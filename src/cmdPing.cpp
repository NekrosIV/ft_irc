/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:08 by pscala            #+#    #+#             */
/*   Updated: 2025/05/28 06:21:33 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"

void Serveur::cmdPing(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		sendError(client, 461, "PING", "Not enough parameters");
		return;
	}

	std::ostringstream oss;
	oss << "PONG :" << params[0] << "\r\n";

	TryToSend(client, oss.str());
}
