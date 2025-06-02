/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:52:19 by pscala            #+#    #+#             */
/*   Updated: 2025/06/02 04:01:43 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "Client.hpp"

static bool isValidUsername(const std::string& name)
{
    char c;
    for (size_t i = 0; i < name.length(); i++)
    {
        c = name[i];
        if(c == ' ' || c == '@' || c == '\r' || c == '\n' || c == '\0')
            return false;
    }
    return true;
}

void Serveur::cmdUser(Client &client, const std::vector<std::string> &params)
{
    if(client.get_hasPass() == false)
		cmdError(client,"Access denied by configuration");

    if (client.isRegistered())
    {
        sendError(client, 462, "USER", "You may not reregister");
        return;
    }

    if(params.size() < 4)
    {
        sendError(client, 461, "USER", "Not enough parameters");
        return;
    }

    if(!isValidUsername(params[0]))
    {
        sendError(client, 432, params[0], "Erroneous username");
        return;
    }

    client.setUsername(params[0]);

    client.setRealname(params[3]);

    client.testRegistered();
    if(client.isRegistered() == true)
        sendWelcomeMessages(client);
}
