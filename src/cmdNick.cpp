/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:58 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 04:20:41 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"


bool	isSpecial(char c)
{
	return c == '-' || c == '[' || c == ']' || c == '\\' ||
           c == '`' || c == '^' || c == '{' || c == '}';
}

bool	isValidNickname(std::string name)
{
	if (name.size() > 9)
		return false;

	if (!isalpha(name[0]) && !isSpecial(name[0]))
        return false;

	for (size_t i = 1; i < name.length(); ++i)
	{
		if (!isalnum(name[0]) && !isSpecial(name[0]))
			return false;
	}
	return true;
}

void Serveur::cmdNick(Client &client, const std::vector<std::string>& params)
{

	if (params.size() < 1)
	{
		sendError(client, 431, "NICK", "No nickname given");
        return;
	}

	if (client.getNickname() == params[0])
		return;


	if (FindClient(params[0]) != NULL)
	{
		sendError(client, 433, params[0], "Nickname is already in use");
			return;
	}

	if (!isValidNickname(params[0]))
	{
		sendError(client, 432, params[0], "Erroneous nickname");
		return;
	}

	std::string old_name = client.getNickname();

	client.setNickname(params[0]);

	if(!old_name.empty())
	{
		std::ostringstream msg;
		msg << ":" << old_name << "!" << client.getUsername() << "@localhost" << " NICK " << client.getNickname() << "\r\n";
		const std::set<Channel*>& chans = client.getJoinedChannels();
		if (!chans.empty())
		{
			for (std::set<Channel*>::const_iterator it = chans.begin(); it != chans.end(); ++it)
			broadcastToChannel(*it, msg.str());
		}
		else
			TryToSend(client, msg.str());
	}
	client.testRegistered();
}
