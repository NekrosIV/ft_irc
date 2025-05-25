/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:06 by kasingh           #+#    #+#             */
/*   Updated: 2025/04/25 16:13:44 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <iostream>

class Serveur
{
  private:
	int _port;
	std::string _password;

  public:
	Serveur(int port, std::string &password);
	~Serveur();
	void start();
};
