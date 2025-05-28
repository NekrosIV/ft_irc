/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:06 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/28 02:03:23 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utils.hpp"

#define MAXEVENTS 1000

typedef void (Serveur::*CommandFunc)(Client &, const std::string &);

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
	std::map<std::string, CommandFunc> _commands;
	std::set<std::string> _ClientsNicknames;

  public:
	Serveur(int port, std::string &password);
	~Serveur();
	void start();
	void run();
	void setNonBlockSocket(const int fd);
	void handleClientEvents(const struct epoll_event &ev);
	Client *FindClient(const int fd);
	void removeClient(Client *client);
	void handleClientCommand(Client &client, std::string line);
	void TryToSend(Client &client, std::string &msg);

	void cmdNick(Client &client, const std::string &params);
    void cmdJoin(Client &client, const std::string &params);
    void cmdQuit(Client &client, const std::string &params);
	void cmdUser(Client &client, const std::string &params);
    void cmdPing(Client &client, const std::string &params);
    void cmdPart(Client &client, const std::string &params);
    void cmdKick(Client &client, const std::string &params);
    void cmdMode(Client &client, const std::string &params);
    void cmdTopic(Client &client, const std::string &params);
    void cmdInvite(Client &client, const std::string &params);
    void cmdNotice(Client &client, const std::string &params);
    void cmdPrivmsg(Client &client, const std::string &params);
};

