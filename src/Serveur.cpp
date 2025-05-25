/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:54:45 by kasingh           #+#    #+#             */
/*   Updated: 2025/04/25 16:14:04 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"

Serveur::Serveur(int port, std::string &password)
{
	_port = port;
	_password = password;
}

Serveur::~Serveur()
{
}

void Serveur::start()
{
    
}