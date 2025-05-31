/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdError.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:29:02 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/29 22:32:32 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Serveur.hpp"
#include "Client.hpp"

void Serveur::cmdError(Client &client, std::string reason)
{
	std::ostringstream msg;

	msg << "ERROR :Closing link: (" 
	    << (client.getNickname().empty() ? "*" : client.getNickname())
	    << "@" << "127.0.0.1"
	    << ") [" << reason << "]\r\n";

	TryToSend(client, msg.str());
    removeClient(&client);
}