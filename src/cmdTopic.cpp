/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:16 by pscala            #+#    #+#             */
/*   Updated: 2025/06/01 05:37:21 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Channel.hpp"
#include "Client.hpp"



void Serveur::cmdTopic(Client &client, const std::vector<std::string>& params)
{
	if (params.empty())
	{
		sendError(client, 461, "TOPIC", "Not enough parameters");
		return;
	}
	
	const std::string &channelName = params[0];
	
	if(!channelExists(channelName))
	{
		sendError(client, 403, channelName, "No sush channel");
		return;
	}

	Channel	*channel = getChannel(channelName);

	if(!channel->isMember(&client))
	{
		sendError(client, 442, channelName, "You're not on that channel");
		return;
	}
	
	if(params.size() == 1)
	{
		if(channel->getTopic().empty())
		{
			std::ostringstream msg;
			msg << ":" << _servername << " 331 " << client.getNickname() << " "
				<< channelName << " :No topic is set\r\n";
			TryToSend(client, msg.str());
		}
	}
	else
	{
		std::ostringstream msg;
		msg << ":" << _servername << " 331 " << client.getNickname() << " "
			<< channelName << " :" << channel->getTopic() << "\r\n";
		TryToSend(client, msg.str());
	}

	if(channel->isTopicRestricted() && !channel->isOperator(&client))
	{
		sendError(client, 482, channelName, "You're not channel operator");
		return;
	}
	const std::string &newTopic = params[1];
	channel->setTopic(newTopic);

	std::ostringstream msg;
	msg << ":" << client.getPrefix() << " TOPIC " << channelName << " :"
		<< newTopic << "\r\n";
	broadcastToChannel(channel, msg.str());
}
