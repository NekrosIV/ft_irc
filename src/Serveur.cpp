/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:54:45 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/27 21:36:24 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"

Serveur::Serveur(int port, std::string &password)
{
	_port = port;
	_password = password;
	_server_fd = -1;
}

Serveur::~Serveur()
{
	if (_server_fd > 0)
		close(_server_fd);
	for (std::vector<Client>::const_iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
		it->close_fd();
}

void Serveur::start()
{
	struct sockaddr_in	my_sockaddr;
	struct epoll_event	ev;

	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	CheckSyscall(_server_fd, "socket()");
	setNonBlockSocket(_server_fd);
	std::memset(&my_sockaddr, 0, sizeof(my_sockaddr));
	my_sockaddr.sin_family = AF_INET;
	my_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_sockaddr.sin_port = htons(_port);
	CheckSyscall(bind(_server_fd, (struct sockaddr *)(&my_sockaddr), sizeof(my_sockaddr)), "bind()");
	CheckSyscall(listen(_server_fd, 1000), "listen()");
	ev.events = EPOLLIN;
	ev.data.fd = _server_fd;
	_epollfd = epoll_create1(0);
	CheckSyscall(_epollfd, "epoll_create1()");
	CheckSyscall(epoll_ctl(_epollfd, EPOLL_CTL_ADD, _server_fd, &ev), "epoll_ctl()");
}

void Serveur::run()
{
	int client_fd;
	// std::cout << BGREEN << "Server is waiting..." << RESET << std::endl;
	int nfds = epoll_wait(_epollfd, _events, MAXEVENTS, -1);
	CheckSyscall(nfds, "epoll_wait()");
	for (int i = 0; i < nfds; ++i)
	{
		if (_events[i].data.fd == _server_fd)
		{
			struct epoll_event ev;
			client_fd = accept(_server_fd, 0, 0);
			CheckSyscall(client_fd, "accept()");
			setNonBlockSocket(client_fd);
			ev.data.fd = client_fd;
			ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP | EPOLLERR;
			CheckSyscall(epoll_ctl(_epollfd, EPOLL_CTL_ADD, client_fd, &ev), "epoll_ctl_ADD()");
			_clients_vec.push_back(Client(client_fd));
			std::cout << BGREEN << "Accepted client with fd: " << BWHITE << client_fd << RESET << std::endl;
		}
		else
		{
			handleClientEvents(_events[i]); //pas fini donc pas encore test
		}
	}
}

void Serveur::handleClientEvents(const struct epoll_event& ev)
{
	Client *client = FindClient(ev.data.fd);
	if (!client)
	{
		std::cerr << "recieved event for unknown fd : " << ev.data.fd << std::endl;
    	CheckSyscall(epoll_ctl(_epollfd, EPOLL_CTL_DEL, ev.data.fd, NULL), "epoll_ctl_DEL()");
    	close(ev.data.fd);
   		return;
	}

	if (ev.events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
	{
		removeClient(client);
		return;
	}

	if (ev.events & EPOLLIN)
	{
		char buffer[1024];
		int n = recv(client->getFd(), buffer, sizeof(buffer), 0);
		if (n <= 0)
		{
			removeClient(client);
			return;
		}
		try
		{
			client->FillReadBuffer(std::string(buffer, n));
		}
		catch (const std::exception& e)
		{
			std::cerr << "Client buffer " << client->getFd() << " overflow: " << e.what() << std::endl;
			removeClient(client);
			return;
		}
		std::string line;
		while (client->getCmdNextLine(line))
		{
			handleClientCommand(*client, line);
		}
	}
}

Client *Serveur::FindClient(const int fd)
{
	for (std::vector<Client>::iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
		if (it->getFd() == fd)
			return &(*it);
	return NULL;
}

void	Serveur::removeClient(Client *client)
{
	std::cout << "Coucou" << std::endl;
	CheckSyscall(epoll_ctl(_epollfd, EPOLL_CTL_DEL, client->getFd(), NULL), "epoll_ctl()");
	client->close_fd();
	std::cout << BYELLOW << "Client " << client->getUsername() << " disconnected." << RESET << std::endl;
	for (std::vector<Client>::iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
	{
		if (&(*it) == client)
		{
			// std::cout << "hey" << std::endl;
			_clients_vec.erase(it);
			break;
		}
	}
}

t_parsed_command parseIrcCommand(const std::string line)
{
	t_parsed_command result;
	result.prefix = "";
	result.command = "";
	result.params.clear();

	std::string remaining = line ;
	
	// Etape 1 on extrait le prefix;
	if(!remaining.empty() && remaining[0] == ':')
	{
		size_t space = remaining.find(' ');
		if(space != std::string::npos)
		{
			result.prefix = remaining.substr(1, space - 1);
			remaining = remaining.substr(space + 1);
		}
		else
			return result;
	}
	
	std::istringstream iss(remaining);
	std::string token;
	bool trailingStarted = false;
	
	// Etap	2 on extrait la commande
	if(!(iss >> result.command))
		return result; 
	
	// Etape 3 on extrait les 14 patametre
	while (iss >> token)
	{
		if(token[0] == ':' && !trailingStarted)
		{
			trailingStarted = true;
			std::string trailing = token.substr(1);
			std::string rest;
			std::getline(iss, rest);
			trailing += rest;
			result.params.push_back(trailing);
			break;
		}
		else
		{
			if(result.params.size() < 14)
				result.params.push_back(token);
			else
				break;
		}
	}
	return(result);
}

void	Serveur::handleClientCommand(Client &client, std::string line)
{
	t_parsed_command cmd = parseIrcCommand(line);
	
	std::cout << "================= Parsed Command =================" << std::endl;
	std::cout << "Raw line: \"" << line << "\"" << std::endl;

	if (!cmd.prefix.empty())
		std::cout << "Prefix   : [" << cmd.prefix << "]" << std::endl;
	else
		std::cout << "Prefix   : [none]" << std::endl;

	std::cout << "Command  : [" << cmd.command << "]" << std::endl;

	std::cout << "Params   : (" << cmd.params.size() << " param(s))" << std::endl;
	for (size_t i = 0; i < cmd.params.size(); ++i)
		std::cout << "  Param[" << i << "] : [" << cmd.params[i] << "]" << std::endl;

	std::cout << "==================================================" << std::endl;
	
}

void Serveur::setNonBlockSocket(const int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	CheckSyscall(flags, "get fcntl()");
	CheckSyscall(fcntl(fd, F_SETFL, flags | O_NONBLOCK), "set fcntl()");
}

void CheckSyscall(const int res, const std::string& context)
{
    if (res < 0)
    {
        std::string err = context + ": " + std::strerror(errno);
        throw std::runtime_error(err);
    }
}

void Serveur::TryToSend(Client &client, std::string &msg)
{
	size_t sent = send(client.getFd(), msg.c_str(), msg.length(), 0);
	if (sent < 0)
		{
			 if (errno == EAGAIN || errno == EWOULDBLOCK)
			 {
				 client.FillWriteBuffer(msg);
				 //continuer la mise en place av epollout, peut etre rajouter le bool wantstowrite a true dans FillWriteBuffer jsp trop
			 }
			 else
			 	removeClient(&client);
		}
		else if (sent < (size_t)msg.length())
		{
			client.FillWriteBuffer(msg.substr(sent));
			//continuer la mise en place av epollout, peut etre rajouter le bool wantstowrite a true dans FillWriteBuffer jsp trop


		}
}
