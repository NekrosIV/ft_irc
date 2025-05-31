/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:53 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 07:47:11 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool	Serveur::testKick(Client &client, Client &target, Channel *channel)
{
	if (!channel->isMember(&client))
	{
		sendError(client, 442, channel->getChannelName(), "You're not on that channel");
   		return false;
	}

	if (!channel->isOperator(&client))
	{
		sendError(client, 482, channel->getChannelName(), "You're not channel operator");
   		return false;
	}

	if (&client == &target)
		return false;

	if (!channel->isMember(&target))
	{
		sendError(client, 441,  client.getNickname() + " " + channel->getChannelName() , "They aren't on that channel");
   		return false;
	}

	return true;
}

void	Serveur::kickClient(Client &client, Channel *channel)
{
	channel->RemoveClient(&client);
	client.leaveChannel(channel);
}

void Serveur::cmdKick(Client &client, const std::vector<std::string> &params)
{
	if (params.size() < 2)
	{
		sendError(client, 461, "KICK", "Not enough parameters");
		return;
	}

	std::vector<std::string>  chanNames = splitCommaList(params[0]);
	std::vector<std::string>  clientNames = splitCommaList(params[1]);

	if (chanNames.size() > clientNames.size())
	{
		sendError(client, 461, "KICK", "Not enough parameters");
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

		if (!testKick(client, *target, channel))
			continue;

		std::ostringstream oss;
		oss << client.getPrefix() << " KICK " << chanName << " " << targetName;

		if (params.size() > 2)
			oss << " :" << params[2];
		else
			oss << " :" << client.getNickname();

		oss << "\r\n";
		broadcastToChannel(channel, oss.str());

		kickClient(*target, channel);
	}
}
