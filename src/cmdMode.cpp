/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:55 by pscala            #+#    #+#             */
/*   Updated: 2025/06/01 03:52:37 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Serveur.hpp"

void Serveur::cmdMode(Client &client, const std::vector<std::string> &params)
{
	Channel	*channel;
	bool	adding;
	size_t	paramIndex;
	char	mode;

	if (params.empty())
	{
		sendError(client, 461, "PART", "Not enough parameters");
		return ;
	}
	std::string channelName = params[0];
	if (!channelExists(channelName))
	{
		sendError(client, 403, channelName, "No such channel");
		return ;
	}
	channel = getChannel(channelName);
	if (params.size() == 1)
	{
		// send les mod sur le channel
		return ;
	}
	if (!channel->isOperator(&client))
	{
		sendError(client, 482, channelName, "You're not channel operator");
		return ;
	}
	std::string modeStr = params[1];
	adding = true;
	paramIndex = 2;
	for (size_t i = 0; i < modeStr.size(); ++i)
	{
		mode = modeStr[i];
		if (mode == '+')
		{
			adding = true;
			continue ;
		}
		else if (mode == '-')
		{
			adding = false;
			continue ;
		}
		switch (mode)
		{
		case 'i':
		{
			channel->setInviteOnly(adding);
			std::ostringstream msg;
			msg << ":" << client.getPrefix() << " MODE " << channelName << " "
				<< (adding ? "+i" : "-i") << "\r\n";
			broadcastToChannel(channel, msg.str());
			break ;
		}
		case 't':
		{
			channel->setTopicRestricted(adding);
			std::ostringstream msg;
			msg << ":" << client.getPrefix() << " MODE " << channelName << " "
				<< (adding ? "+t" : "-t") << "\r\n";
			broadcastToChannel(channel, msg.str());
			break ;
		}
		case 'k':
		{
			if(adding)
			{
				if(paramIndex >= params.size())
				{
					sendError(client, 461, "MODE", "Not enough parameters for +k");
					break;
				}
				channel->setPassword(params[paramIndex++]);
			}
			else
			{
				channel->setPassword("");
			}
			std::ostringstream msg;
			msg << ":" << client.getPrefix() << " MODE " << channelName << " "
				<< (adding ? "+k " : "-k") << (adding ? " " + channel->getPassword() : "") <<"\r\n";
			broadcastToChannel(channel, msg.str());
			break ;
		}
		case 'l':
		{
			if(adding)
			{
				if(paramIndex >= params.size())
				{
					sendError(client, 461, "MODE", "Not enough parameters for +l");
					break;
				}
				std::istringstream iss(params[paramIndex++]);
				int limit;
				if(!(iss >> limit) || limit <= 0)
				{
					sendError(client, 461, "MODE", "Invalid limit parameter for +l");
					break;
				}
				channel->setLimit(limit);
			}
			else
			{
				channel->setLimit(-1);
			}
			std::ostringstream msg;
			msg << ":" << client.getPrefix() << " MODE " << channelName << " "
				<< (adding ? "+l " + std::string(params[paramIndex - 1]) : "-l") <<"\r\n";
			broadcastToChannel(channel, msg.str());
			break ;
		}
		case 'o':
		{
			if(paramIndex >= params.size())
			{
				sendError(client, 461, "MODE", "Not enough parameters for +o/-o");
				break;
			}
			std::string targetNick = params[paramIndex++];
			Client *target = FindClient(targetNick);
			if(!target || !channel->isMember(target))
			{
				sendError(client, 441, "MODE", "They aren't on that channel");
				break;
			}
			if(adding)
				channel->addOperator(target);
			else
				channel->RemoveOperator(target);
			std::ostringstream msg;
			msg << ":" << client.getPrefix() << " MODE " << channelName << " "
				<< (adding ? "+o " : "-o ") << targetNick <<"\r\n";
			broadcastToChannel(channel, msg.str());
				break ;
		}
		default:
			sendError(client, 472, std::string(1, mode), "is unknow mode char");
			break ;
		}
	}
}
