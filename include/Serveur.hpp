/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:06 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/31 07:30:36 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utils.hpp"

#define MAXEVENTS 1000

class	Client;
class	Channel;

class Serveur
{
  public:
	typedef void (Serveur::*CommandFunc)(Client &,
		const std::vector<std::string> &);

	Serveur(int port, std::string &password);
	~Serveur();

	void start();
	void run();
	void setNonBlockSocket(const int fd);
	void handleClientEvents(const struct epoll_event &ev);
	Client *FindClient(const int fd);
	Client *FindClient(const std::string &name);
	void removeClient(Client *client);
	void handleClientCommand(Client &client, std::string line);
	int TryToSend(Client &client, std::string msg);
	void sendWelcomeMessages(Client &client);

	void sendError(Client &client, int code, const std::string &arg, const std::string &message);
	void enableWriteEvent(Client &client);
	void disableWriteEvent(Client &client);
	Channel *getChannel(const std::string &name);
	Channel *getOrCreateChannel(const std::string &name);
	void broadcastToChannel(Channel *channel, const std::string &message);
	bool channelExists(const std::string &name) const;
	void deleteChannel(const std::string &name);

	void cmdNick(Client &client, const std::vector<std::string> &params);
	void cmdJoin(Client &client, const std::vector<std::string> &params);
	void joinSingleChannel(Client &client, const std::string &chanName, const std::string &key);
	void cmdQuit(Client &client, const std::vector<std::string> &params);
	void cmdUser(Client &client, const std::vector<std::string> &params);
	void cmdPing(Client &client, const std::vector<std::string> &params);
	void cmdPart(Client &client, const std::vector<std::string> &params);
	void cmdPass(Client &client, const std::vector<std::string> &params);
	void cmdKick(Client &client, const std::vector<std::string> &params);
	void cmdMode(Client &client, const std::vector<std::string> &params);
	void cmdTopic(Client &client, const std::vector<std::string> &params);
	void cmdInvite(Client &client, const std::vector<std::string> &params);
	void cmdNotice(Client &client, const std::vector<std::string> &params);
	void cmdPrivmsg(Client &client, const std::vector<std::string> &params);
	bool testKick(Client &client, Client &target, Channel *channel);
	void kickClient(Client &client, Channel *channel);
	bool testInvite(Client &client, Client &target, Channel *channel);



	void cmdError(Client &client, std::string reason);

  private:
	int _port;
	int _server_fd;
	int _epollfd;
	std::string _password;
	struct epoll_event _events[MAXEVENTS];
	std::vector<Client *> _clients_vec;
	std::map<std::string, CommandFunc> _commands;
	std::set<std::string> _ClientsNicknames;
	std::string _servername;
	std::string _serverVersion;
	std::map<std::string, Channel *> _channels;
};
