/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:06 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/25 17:45:17 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client.hpp"
#include <arpa/inet.h> // inet_ntoa() si tu veux convertir adresse IP
#include <cstdlib>
#include <cstdlib>      // exit, atoi, strtol
#include <cstring>      // memset (pour struct sockaddr_in), strerror
#include <errno.h>      // errno pour messages d’erreur système
#include <fcntl.h>      // fcntl() pour mettre le socket en non-bloquant
#include <iostream>     // std::cout, std::cerr
#include <netinet/in.h> // sockaddr_in, htons(), htonl(), INADDR_ANY
#include <string>       // std::string
#include <sys/epoll.h>  // poll() et struct pollfd
#include <sys/socket.h> // socket(), bind(), listen(), setsockopt()
#include <sys/types.h>  // types systèmes : socket, bind, etc.
#include <unistd.h>     // close()
#include <vector>

#define MAXEVENTS 1000

class	Client;

class Serveur
{
  private:
	int _port;
	int _socketfd;
	int _epollfd;
	std::string _password;
	struct epoll_event _events[MAXEVENTS];
	std::vector<Client> _clients_vec;

  public:
	Serveur(int port, std::string &password);
	~Serveur();
	void start();
	void run();
};