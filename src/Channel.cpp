/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 07:03:29 by pscala            #+#    #+#             */
/*   Updated: 2025/05/28 07:34:13 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string name)
{
}

Channel::~Channel()
{
}

void Channel::AddClient(const Client *newMember)
{
}

void Channel::RemoveClient(const Client *member)
{
}

void Channel::RemoveOperator(const Client *op)
{
}

const std::string &Channel::getChannelName() const
{
	return (_name);
}

const std::set<Client *> &Channel::getClients() const
{
	return (_members);
}
