/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:49 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 04:39:51 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void Serveur::joinSingleChannel(Client &client, const std::string &chanName, const std::string &key)
{
	if(chanName.empty() || chanName[0] != '#')
	{
		sendError(client, 479, chanName, "Bad channel mask");
		return;
	}
	
	Channel *chan = getOrCreateChannel(chanName);

	if(chan->isMember(&client))
		return;
		
	if(chan->isBanned(&client))
	{
		sendError(client, 474, chanName, "You are banned from this channel");
		return;
	}
	
	if(chan->isInvitedOnly() && !chan->isInvited(&client))
	{
		sendError(client, 473, chanName, "Cannot join channel (+i)");
		return;
	}
	
	if(chan->getLimit() > 0 && chan->getClients().size() >= chan->getLimit())
	{
		sendError(client, 471 , chanName, "Cannot join channel (+l)");
		return;
	}

	chan->AddClient(&client);
	client.joinChannel(chan);
	// chan->removeInvitation(&client);
	
	if (chan->getClients().size() == 1)
		chan->addOperator(&client);
	std::ostringstream joinMsg;
	
	joinMsg << ":" << client.getPrefix() << "JOIN" << chanName << "\r\n";
	broadcastToChannel(chan,joinMsg.str());
	
	std::ostringstream names;
	names << ":" << _servername << " 353 " << client.getNickname()
	      << " = " << chanName << " :";

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

void Serveur::cmdJoin(Client &client, const std::vector<std::string> &params)
{
	if(params.empty())
	{
		sendError(client, 461, "JOIN", "Not enough parameters");
		return;
	}

	if(params[0] == "0")
	{
		const std::set<Channel *> &joined = client.getJoinedChannels();
		for (std::set<Channel *>::iterator it = joined.begin(); it != joined.end(); ++it)
			cmdPart(client, std::vector<std::string>(1, (*it)->getChannelName()));
		return;
	}

	std::vector<std::string>  chanNames = splitCommaList(params[0]);
	std::vector<std::string> keys;
	if(params.size() > 1)
		keys = splitCommaList(params[1]);
	
	for (size_t i = 0; i < chanNames.size(); ++i)
	{
		std::string chanName = chanNames[i];
		std::string key = (i < keys.size()) ? keys[i] : "";
		
		joinSingleChannel(client,chanName,key);
	}

}
