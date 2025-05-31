/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:46 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 07:43:58 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool	Serveur::testInvite(Client &client, Client &target, Channel *channel)
{
	if (!channel->isMember(&client))
	{
		sendError(client, 442, channel->getChannelName(), "You're not on that channel");
   		return false;
	}

	if (channel->isInvitedOnly() && !channel->isOperator(&client))
	{
		sendError(client, 482, channel->getChannelName(), "You're not channel operator");
   		return false;
	}

	if (&client == &target)
		return false;

	if (channel->isMember(&target))
	{
		sendError(client, 443,  client.getNickname() + " " + channel->getChannelName() , "is already on channel");
   		return false;
	}

	return true;
}

void Serveur::cmdInvite(Client &client, const std::vector<std::string> &params)
{
	if (params.size() < 2)
	{
		sendError(client, 461, "INVITE", "Not enough parameters");
		return;
	}

	std::vector<std::string>  chanNames = splitCommaList(params[0]);
	std::vector<std::string>  clientNames = splitCommaList(params[1]);

	if (chanNames.size() > clientNames.size())
	{
		sendError(client, 461, "INVITE", "Not enough parameters");
		return;
	}

	for (size_t i = 0; i < chanNames.size(); ++i)
	{
		std::string chanName = chanNames[i];
		std::string targetName;

		if (clientNames.size() == 1)
			targetName = clientNames[0];
		else
			targetName = clientNames[i];


		Channel *channel = getChannel(chanName);
		if (!channel)
		{
			sendError(client, 403, chanName, "No such channel");
			continue;
		}

		Client *target = FindClient(targetName);
		if (!target)
		{
			sendError(client, 401, targetName, "No such nick");
			continue;
		}

		if (!testInvite(client, *target, channel))
			continue;

		std::ostringstream oss;
		oss << client.getPrefix() << " INVITE " << targetName << " :" << chanName << "\r\n";
		TryToSend(*target, oss.str());

		channel->invite(target);

		std::ostringstream reply;
		reply << ":irc.42.fr 341 " << client.getNickname() << " "
      	<< target->getNickname() << " " << channel->getChannelName() << "\r\n";
		TryToSend(client, reply.str());
	}
}
