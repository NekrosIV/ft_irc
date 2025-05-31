/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:08 by pscala            #+#    #+#             */
/*   Updated: 2025/05/29 04:31:06 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"

void Serveur::cmdPing(Client &client, const std::vector<std::string>& params)
{
	if (params.empty())
	{
		sendError(client, 409, "PING", "No origin specified");
		return;
	}

	std::string msg = "PONG " + _servername + " :" + params[0] + "\r\n";

	TryToSend(client, msg);
}
