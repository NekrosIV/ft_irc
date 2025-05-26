/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:27:13 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/26 07:05:29 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _isRegistered(false), _isOperator(false),
	_wantsToWrite(false)
{
}

void Client::close_fd() const
{
	if (_fd >= 0)
		close(_fd);
}

const std::string &Client::getNickname() const
{
	return (_nickname);
}

void Client::setNickname(const std::string Nname)
{
	_nickname = Nname;
}

const std::string &Client::getUsername() const
{
	return (_username);
}

void Client::setUsername(const std::string Uname)
{
	_username = Uname;
}

int Client::getFd() const
{
	return (_fd);
}

void Client::testRegistered()
{
	if (!_username.empty() && !_nickname.empty())
		_isRegistered = true;
}

void Client::joinChannel(Channel *channel)
{
	if (_joinedChannels.count(channel))
		return ;
	_joinedChannels.insert(channel);
	channel->AddClient(this);
}

void Client::leaveChannel(Channel *channel)
{
	_joinedChannels.erase(channel);
	channel->RemoveClient(this);
}

void Client::FillReadBuffer(const std::string &read)
{
	if (_readBuffer.size() + read.size() > 10000)
		throw std::runtime_error("Client buffer overflow");
	_readBuffer += read;
}

bool Client::getCmdNextLine(std::string &line)
{
	size_t	pos;

	pos = _readBuffer.find("\r\n");
	if (pos == std::string::npos)
		return (false);
	line = _readBuffer.substr(0, pos);
	_readBuffer.erase(0, pos + 2);
	return (true);
}
