/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNotice.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:01 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 03:40:42 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void Serveur::cmdNotice(Client &client, const std::vector<std::string>& params)
{
	if (!client.isRegistered())
	{
		sendError(client, 451, " NOTICE ", "You have not registered");
		return;
	}

	if (params.size() < 2)
        return;

	std::string message;
	for (size_t i = 1; i < params.size(); ++i)
	{
		if (i > 1)
			message += " ";
		message += params[i];
	}

	Channel *targetChannel = getChannel(params[0]);
	if (targetChannel)
	{
		if (!targetChannel->isMember(&client))
			return;

		std::ostringstream oss;
		oss << ":" << client.getPrefix() << " PRIVMSG " << targetChannel->getChannelName() << " :" << message << "\r\n";

		const std::set<Client*>& members = targetChannel->getClients();
		for (std::set<Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
		{
			if (*it != &client)
				TryToSend(**it, oss.str());
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
