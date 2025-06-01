/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:53 by pscala            #+#    #+#             */
/*   Updated: 2025/06/01 06:20:25 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

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
	std::string comment = (params.size() > 2) ? params[2] : client.getNickname();

	if (chanNames.size() != 1 && chanNames.size() != clientNames.size())
	{
		sendError(client, 461, "KICK", "Mismatched number of channels and users");
		return;
	}

	for (size_t i = 0; i < chanNames.size(); ++i)
	{
		std::string chanName = (chanNames.size() == 1) ? chanNames[0] : chanNames[i]; 
		std::string clientName = clientNames[i];


		Channel *channel = getChannel(chanName);
		if (!channel)
		{
			sendError(client, 403, chanName, "No such channel");
			continue;
		}

		if (!channel->isMember(&client))
		{
			sendError(client, 442, chanName, "You're not on that channel");
   			continue;
		}
	
		if (!channel->isOperator(&client))
		{
			sendError(client, 482, chanName, "You're not channel operator");
   			continue;
		}

		Client *target = FindClient(clientName);
		if (!target)
		{
			sendError(client, 401, clientName, "No such nick");
			continue;
		}

		if (target == &client)
			continue;

		if (!channel->isMember(target))
		{
			sendError(client, 442, chanName, " :They aren't on that channel");
   			continue;
		}

		std::ostringstream msg;
		msg << client.getPrefix() << " KICK " << chanName << " " << clientName 
			 << " :" << comment << "\r\n";
		broadcastToChannel(channel, msg.str());

		kickClient(*target, channel);
	}
}
