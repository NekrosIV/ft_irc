/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:10 by pscala            #+#    #+#             */
/*   Updated: 2025/05/28 08:09:31 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Client *Serveur::FindClient(const std::string &name)
{

	for (std::vector<Client>::iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
		if (it->getNickname() == name)
			return &(*it);
	return NULL;

}

bool Serveur::channelExists(const std::string& name) const
{
	for (std::set<Channel*>::const_iterator it = _Channels.begin(); it != _Channels.end(); ++it)
	{
		if ((*it)->getChannelName() == name)
			return true;
	}
	return false;
}

void Serveur::cmdPrivmsg(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 2)
	{
		sendError(client, 461, "PRIVMSG", "Not enough parameters");
        return;
	}

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

	else if (channelExists(params[0]))
	{
		sendError(client, 442, params[0], "You're not on that channel");
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

	sendError(client, 401, params[0], "No such nick/channel");
}
