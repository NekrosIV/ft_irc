/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:36 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/27 03:01:55 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "color.h"

class	Serveur;
class	Channel;

class Client
{
  private:
	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _readBuffer;
	std::string _writeBuffer;

	bool _isRegistered;
	bool _isOperator;
	bool _wantsToWrite;

	std::set<Channel *> _joinedChannels;

  public:
	Client(const int fd);
	void close_fd() const;
	const std::string &getNickname() const;
	void setNickname(const std::string Nname);
	const std::string &getUsername() const;
	void setUsername(const std::string Uname);
	int getFd() const;
	bool isRegistered() const;
	void testRegistered();
	void joinChannel(Channel *channel);
	void leaveChannel(Channel *channel);
	void FillReadBuffer(const std::string &read);
	void FillWriteBuffer(const std::string &read);
	bool getCmdNextLine(std::string &line);
	bool WantsToRight();
};
