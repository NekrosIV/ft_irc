/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNotice.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:01 by pscala            #+#    #+#             */
/*   Updated: 2025/05/28 08:09:11 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void Serveur::cmdNotice(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 2)
        return;

	std::string message;
	for (size_t i = 1; i < params.size(); ++i)
	{
		if (i > 1)
			message += " ";
		message += params[i];
	}

	Channel *targetChannel = client.FindChannel(params[0]);
	if (targetChannel)
	{
		for (std::set<Client*>::const_iterator it = targetChannel->getClients().begin(); it != targetChannel->getClients().end(); ++it)
		{
			if (*it != &client)
			{
				std::ostringstream oss;
				oss << client.getPrefix() << " PRIVMSG " << targetChannel->getChannelName() << " :" << message << "\r\n";
				TryToSend(**it, oss.str());
			}
		}
		return;
	}

	Client	*targetClient = FindClient(params[0]);
	if (targetClient)
	{
		std::ostringstream oss;
		oss << client.getPrefix() << " PRIVMSG " << targetClient->getNickname() << " :" << message << "\r\n";
		TryToSend(*targetClient, oss.str());
		return;
	}
}
