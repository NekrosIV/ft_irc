/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:36 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/25 17:49:36 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Serveur.hpp"

class	Serveur;

class Client
{
  private:
	int _fd;

  public:
	Client(int fd);
	void close_fd() const;
};