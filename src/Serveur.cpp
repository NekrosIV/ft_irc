/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:54:45 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/26 06:49:49 by pscala           ###   ########.fr       */
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
	std::cout << BGREEN << "Server is waiting..." << RESET << std::endl;
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
			ev.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
			CheckSyscall(epoll_ctl(_epollfd, EPOLL_CTL_ADD, client_fd, &ev), "epoll_ctl()");
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
    	epoll_ctl(_epollfd, EPOLL_CTL_DEL, ev.data.fd, NULL);
    	close(ev.data.fd);
   		return;
	}

	if (ev.events & EPOLLRDHUP)
	{
		removeClient(client); //  a faire
		return;
	}

	if (ev.events & EPOLLIN)
	{
		char buffer[1024];
		int n = recv(client->getFd(), buffer, sizeof(buffer), 0);
		if (n <= 0)
		{
			removeClient(client); //  a faire
			return;
		}
		try
		{
			client->FillReadBuffer(std::string(buffer, n));
		}
		catch (const std::exception& e)
		{
			std::cerr << "Client buffer " << client->getFd() << " overflow: " << e.what() << std::endl;
			removeClient(client); // a faire
			return;
		}
		std::string line;
		while (client->getCmdNextLine(line))
		{
			handleClientCommand(*client, line); //a faire
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
	// a faire, retirer client partout ou il est: channel, tableaux de struct etc
}

void	Serveur::handleClientCommand(Client &client, std::string line)
{
	// a faire
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

