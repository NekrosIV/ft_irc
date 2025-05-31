/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 07:03:29 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 07:50:46 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string name)
{
	_name = name;
	_topic = "";
	_password = "";
	_maxMembers = -1;
	_isPrivate = false;
	_isSecret = false;
	_requierPass = false;
	_isInviteOnly = false;

}

Channel::~Channel()
{
}

void Channel::AddClient(Client *newMember)
{
	_members.insert(newMember);
}

void Channel::RemoveClient(Client *member)
{
	_members.erase(member);
	_operators.erase(member);
	_invitedMembers.erase(member);
}

void Channel::RemoveOperator(Client *op)
{
	_operators.erase(op);
}

bool Channel::isMember(Client *client) const
{
	return(_members.find(client) != _members.end());
}

bool Channel::isOperator(Client *client) const
{
	return(_operators.find(client) != _operators.end());
}

bool Channel::isInvitedOnly() const
{
	return(_isInviteOnly);
}

bool Channel::isInvited(Client *client) const
{
	return(_invitedMembers.find(client) != _invitedMembers.end());
}

bool Channel::isBanned(Client *client) const
{
	return(_bannedMembers.find(client) != _bannedMembers.end());
}

void Channel::addOperator(Client *client)
{
	_operators.insert(client);
}

void Channel::invite(Client *client)
{
	if (this->isInvited(client))
		return;
	_invitedMembers.insert(client);
}

void Channel::ban(Client *client)
{
	_bannedMembers.insert(client);
}
void Channel::setPassword(const std::string &pass)
{
	_password = pass;
	_requierPass = true;
}
void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void Channel::setLimit(int limit)
{
	_maxMembers = limit;
}

int Channel::getLimit() const
{
	return(_maxMembers);
}

const std::string &Channel::getTopic() const
{
	return (_topic);
}

const std::string &Channel::getChannelName() const
{
	return (_name);
}

const std::set<Client *> &Channel::getClients() const
{
	return (_members);
}
