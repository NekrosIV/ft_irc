/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:13 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 01:00:47 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Channel.hpp"
#include "Client.hpp"

void Serveur::cmdQuit(Client &client, const std::vector<std::string> &params)
{
	std::string msg;

	if (params.size() == 0 || params[0].empty())
		msg = "Client exited";
	else
		msg = params[0];

	std::ostringstream oss;

	oss << client.getPrefix() << " QUIT " << ":" << msg << "\r\n";

	std::set<Channel*> chans = client.getJoinedChannels();
	if (!chans.empty())
	{
		for (std::set<Channel*>::const_iterator it = chans.begin(); it != chans.end(); ++it)
		{
			Channel* chan = *it;
			broadcastToChannel(chan, oss.str());
			chan->RemoveClient(&client);
			client.leaveChannel(chan);
		
			if (chan->getClients().empty())
				deleteChannel(chan->getChannelName());
		}
	}
	
	std::ostringstream errorMsg;
	errorMsg << "ERROR :Closing Link: " << client.getNickname() << "(" << msg << ")\r\n";
	
	TryToSend(client, errorMsg.str());

	removeClient(&client);
}
