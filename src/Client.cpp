/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:27:13 by kasingh           #+#    #+#             */
/*   Updated: 2025/06/02 04:01:51 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Serveur.hpp"

Client::Client(int fd) : _fd(fd), _isRegistered(false), _isOperator(false), _hasPass(false)
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

void Client::setHasPass(bool status)
{
	_hasPass = status;
}

void Client::setisOperator(bool status)
{
	_isOperator = status;
}

void Client::setRealname(const std::string realname)
{
	_realname = realname;
}

const std::string &Client::getRealname() const
{
	return (_realname);
}

int Client::getFd() const
{
	return (_fd);
}

bool Client::isRegistered() const
{
	return(_isRegistered);
}


bool Client::get_hasPass() const
{
	return(_hasPass);
}

void Client::testRegistered()
{
	if(!isRegistered())
	{
		if (!_username.empty() && !_nickname.empty() && _hasPass)
			_isRegistered = true;
	}
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
		throw std::runtime_error("Buffer overflow");
	_readBuffer += read;
}

void Client::FillWriteBuffer(const std::string &read)
{
	if (_writeBuffer.size() + read.size() > 10000)
		throw std::runtime_error("Buffer overflow");
	_writeBuffer += read;
}

std::string &Client::getWriteBuffer()
{
	return (_writeBuffer);
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

const std::set<Channel *> &Client::getJoinedChannels() const
{
	return (_joinedChannels);
}

std::string Client::getPrefix() const
{
	return(":" + getNickname() + "!" + getUsername() + "@localhost");
}


Channel	*Client::FindChannel(std::string channelName)
{

	for (std::set<Channel*>::const_iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
	{
		if ((*it)->getChannelName() == channelName)
			return *it;
	}
	return NULL;
}
