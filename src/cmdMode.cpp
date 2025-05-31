/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:51:55 by pscala            #+#    #+#             */
/*   Updated: 2025/05/31 05:22:25 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void Serveur::cmdMode(Client &client, const std::vector<std::string> &params)
{
	if(params.empty())
	{
		sendError(client, 461, "PART", "Not enough parameters");
		return;
	}

	std::string channelName = params[0];
	if(!channelExists(channelName))
	{
		sendError(client, 403, channelName, "No such channel");
		return;
	}

	Channel *channel = getChannel(channelName);
	if(params.size() == 1)
	{
		// send les mod sur le channel
		return;
	}

	if(!channel->isOperator(&client))
	{
		sendError(client, 482, channelName, "You're not channel operator");
		return;
	}
	
	
}
