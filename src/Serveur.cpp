/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:54:45 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/25 17:49:40 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"

Serveur::Serveur(int port, std::string &password)
{
	_port = port;
	_password = password;
	_socketfd = -1;
}

Serveur::~Serveur()
{
	if (_socketfd > 0)
		close(_socketfd);
	for (std::vector<Client>::const_iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
		it->close_fd();
}

void Serveur::start()
{
	struct sockaddr_in	my_sockaddr;
	struct epoll_event	ev;

	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd < 0)
		throw std::runtime_error("plus tard");
	// struct sockaddr_in *ptr;
	// ptr = &my_sockaddr;
	// memset(&my_sockaddr,0,sizeof(sockaddr_in));
	// for (size_t i = 0;i < sizeof(sockaddr);i++)
	// 	ptr[i] = ;
	my_sockaddr = sockaddr_in();
	my_sockaddr.sin_family = AF_INET;
	my_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_sockaddr.sin_port = htons(_port);
	if (bind(_socketfd, (struct sockaddr *)(&my_sockaddr),
			sizeof(my_sockaddr)) < 0)
		throw std::runtime_error("plus tard");
	if (listen(_socketfd, 1000))
		throw(std::runtime_error("listen failed"));
	ev.events = EPOLLIN;
	ev.data.fd = _socketfd;
	_epollfd = epoll_create1(0);
	if (_epollfd < 0)
		throw std::runtime_error("epoll failed");
	if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _socketfd, &ev) < 0)
		throw std::runtime_error("epoll fail");
}

void Serveur::run()
{
	int client_fd;
	int nfds = epoll_wait(_epollfd, _events, MAXEVENTS, -1);
	if (nfds < 0)
		throw std::runtime_error("fail epol_wait");
	for (int n = 0; n < nfds; ++n)
	{
		if (_events[n].data.fd == _socketfd)
		{
			struct epoll_event ev;
			client_fd = accept(_socketfd, 0, 0);
			if (client_fd < 0)
				throw std::runtime_error("client fd fail");
			ev.data.fd = client_fd;
			ev.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
			if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, client_fd, &ev) < 0)
				throw std::runtime_error("error epollctl");
			_clients_vec.push_back(Client(client_fd));
			std::cout << "Accepted client with fd: " << client_fd << std::endl;
		}
		else
		{
			// send parsing
		}
	}
}