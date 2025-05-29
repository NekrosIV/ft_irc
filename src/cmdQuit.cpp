/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:13 by pscala            #+#    #+#             */
/*   Updated: 2025/05/29 06:24:28 by pscala           ###   ########.fr       */
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

	for (std::vector<Client>::iterator it = _clients_vec.begin(); it != _clients_vec.end(); ++it)
	{
		if (&(*it) != &client)
			TryToSend(*it, oss.str());
	}

	removeClient(&client);
}
