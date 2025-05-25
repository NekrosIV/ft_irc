/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:15 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/25 17:29:35 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"
#include "color.h"

int	main(int ac, char **av)
{
	char	*endPtr;
	long	port;

	if (ac != 3)
	{
		std::cerr << BRED << "Error need 2 aurgument" << std::endl;
		std::cerr << "Usage: " << av[0] << " <port> <password>" << RESET << std::endl;
		return (1);
	}
	port = strtol(av[1], &endPtr, 10);
	if (*endPtr != '\0' || port < 0 || port > 65535)
	{
		std::cerr << port << " Port is incorecte" << std::endl;
		return (1);
	}
	std::string password = av[2];
	try
	{
		Serveur myServ(port, password);
		myServ.start();
		while (true)
		{
			myServ.run();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}
