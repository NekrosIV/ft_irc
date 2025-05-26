/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:06 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/26 06:41:39 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "color.h"


#define MAXEVENTS 1000

class	Client;

class Serveur
{
  private:
	int _port;
	int _server_fd;
	int _epollfd;
	std::string _password;
	struct epoll_event _events[MAXEVENTS];
	std::vector<Client> _clients_vec;

  public:
	Serveur(int port, std::string &password);
	~Serveur();
	void start();
	void run();
	void setNonBlockSocket(const int fd);
	void	handleClientEvents(const struct epoll_event& ev);
	Client *FindClient(const int fd);
	void	removeClient(Client *client);
	void handleClientCommand(Client &client, std::string line);

};


void CheckSyscall(const int res, const std::string& context);

