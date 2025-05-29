/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:36 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/29 03:38:54 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utils.hpp"

class	Serveur;
class	Channel;

class Client
{
  private:
	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _fullusername;
	std::string _realname;
	std::string _readBuffer;
	std::string _writeBuffer;

	bool _isRegistered;
	bool _isOperator;
	bool _hasPass;

	std::set<Channel *> _joinedChannels;

  public:
	Client(const int fd);
	void close_fd() const;
	void setNickname(const std::string Nname);
	void setUsername(const std::string Uname);
	void setRealname(const std::string realname);
	void setHasPass(bool status);
	void setisOperator(bool status);
	const std::string &getRealname() const;
	const std::string &getNickname() const;
	const std::string &getUsername() const;
	std::string getPrefix() const;
	const std::set<Channel *> &getJoinedChannels() const;
	int getFd() const;
	bool isRegistered() const;
	void testRegistered();
	void joinChannel(Channel *channel);
	void leaveChannel(Channel *channel);
	void FillReadBuffer(const std::string &read);
	void FillWriteBuffer(const std::string &read);
	std::string& getWriteBuffer();
	bool getCmdNextLine(std::string &line);
	Channel	*FindChannel(std::string channelName);

};
