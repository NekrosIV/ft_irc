/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:10 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 00:42:05 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Client *Serveur::FindClient(const std::string &name)
{

	for (std::vector<Client*>::iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
		if ((*it)->getNickname() == name)
			return (*it);
	return NULL;

}

bool Serveur::channelExists(const std::string& name) const
{
	if (name.empty())
		return false;
	return (_channels.find(name) != _channels.end());
}

void Serveur::cmdPrivmsg(Client &client, const std::vector<std::string>& params)
{
	if (!client.isRegistered())
    {
        sendError(client, 462, "PRIVMSG", "You may not reregister");
        return;
    }
	if (params.size() == 0 || params[0].empty())
	{
		sendError(client, 411, "PRIVMSG", "No recipient given");
		return;
	}
	
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

	Channel *targetChannel = getChannel(params[0]);
	if (targetChannel)
	{
		if (!targetChannel->isMember(&client))
		{
			sendError(client, 442, params[0], "You're not on that channel");
			return;
		}
	
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

	sendError(client, 401, params[0], "No such nick/channel");
}
