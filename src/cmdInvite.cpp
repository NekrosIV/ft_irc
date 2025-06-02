/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:46 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 03:41:28 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"


void Serveur::cmdInvite(Client &client, const std::vector<std::string> &params)
{
	if (!client.isRegistered())
	{
		sendError(client, 451, " INVITE ", "You have not registered");
		return;
	}

	if (params.size() < 2)
	{
		sendError(client, 461, "INVITE", "Not enough parameters");
		return;
	}

	const std::string &targetNick = params[0];
	const std::string &channelName = params[1];

	Client *target = FindClient(targetNick);
	if(!target)
	{
		sendError(client, 401, "INVITE", "No Such nick");
		return;
	}

	Channel *channel = getChannel(channelName);

	if(channel)
	{
		if (!channel->isMember(&client))
		{
			sendError(client, 442, channel->getChannelName(), "You're not on that channel");
   			return;
		}
		if (channel->isInvitedOnly() && !channel->isOperator(&client))
		{
			sendError(client, 482, channel->getChannelName(), "You're not channel operator");
   			return;
		}
		if (target == &client)
			return;
		if (channel->isMember(target))
		{
			sendError(client, 443,  targetNick, channelName + " + is already on channel");
   			return;
		}
		channel->invite(target);
	}

	std::ostringstream reply;
	reply << ":" << _servername << " 341 " << client.getNickname()
	      << " " << targetNick << " " << channelName << "\r\n";
	TryToSend(client, reply.str());

	std::ostringstream inviteMsg;
	inviteMsg << ":" << client.getPrefix() << " INVITE " << targetNick
	          << " :" << channelName << "\r\n";
	TryToSend(*target, inviteMsg.str());

}
