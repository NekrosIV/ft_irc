/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:15 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/26 01:02:00 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"

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
		std::cerr << BRED <<  "Port : " << BWHITE << port << BRED << " is incorrect" << RESET << std::endl;
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
		std::cerr << BRED << e.what() << '\n';
		return (1);
	}
	return (0);
}
