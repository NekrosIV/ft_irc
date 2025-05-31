/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:13 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 06:14:55 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
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

	const std::set<Channel*>& chans = client.getJoinedChannels();
	if (!chans.empty())
	{
		for (std::set<Channel*>::const_iterator it = chans.begin(); it != chans.end(); ++it)
		broadcastToChannel(*it, oss.str());
	}
	else
		TryToSend(client, msg);

	removeClient(&client);
}
