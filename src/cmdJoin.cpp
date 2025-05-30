/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:49 by pscala            #+#    #+#             */
/*   Updated: 2025/05/30 04:37:36 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void Serveur::cmdJoin(Client &client, const std::vector<std::string> &params)
{
	if(params.empty())
	{
		sendError(client, 461, "JOIN", "Not enough parameters");
		return;
	}

	const std::string &chanName = params[0];
	if(chanName.empty() || chanName[0] != '#')
	{
		sendError(client, 479, chanName, "Bad channel mask");
		return;
	}
	
	Channel *chan = getOrCreateChannel(chanName);

	if(chan->isMember(&client))
		return;

	if (!chan->getTopic().empty())
	{
		std::ostringstream topic;
		topic << ":" << _servername << " 332 " << client.getNickname() << " "
		      << chanName << " :" << chan->getTopic() << "\r\n";
		TryToSend(client, topic.str());
	}
	else
	{
		std::ostringstream notopic;
		notopic << ":" << _servername << " 331 " << client.getNickname()
		        << " " << chanName << " :No topic is set\r\n";
		TryToSend(client, notopic.str());
	}

	chan->AddClient(&client);
	client.joinChannel(chan);

	std::ostringstream names;
	names << ":" << _servername << " 353 " << client.getNickname()
	      << " = " << chanName << " :";

	const std::set<Client *> &members = chan->getClients();
	for (std::set<Client *>::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		if (it != members.begin()) 
			names << " ";
		if (chan->isOperator(*it))
			names << "@";
		names << (*it)->getNickname();
	}
	names << "\r\n";
	TryToSend(client, names.str());

	std::ostringstream end;
	end << ":" << _servername << " 366 " << client.getNickname()
	    << " " << chanName << " :End of /NAMES list\r\n";
	TryToSend(client, end.str());
}
