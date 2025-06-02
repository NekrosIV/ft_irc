/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:15 by kasingh           #+#    #+#             */
/*   Updated: 2025/06/02 04:55:22 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serveur.hpp"

bool	run = true;

void	handle_quit(int sig)
{
	(void)sig;
	run = false;
}

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
	signal(SIGINT, handle_quit);
	try
	{
		Serveur myServ(port, password);
		myServ.start();

		std::cout << BBLUE
          << "==============================================================\n"
         << BWHITE << "✅  IRC Server started successfully!\n"
          << "🌐  Listening on port " << port << "\n"
          << "👥  Waiting for clients to connect...\n"
          << "🛠️   Supported commands: " << BCYAN << "PASS, NICK, USER, JOIN, PART, PRIVMSG,\n"
          << "     NOTICE, QUIT, KICK, INVITE, TOPIC, MODE\n"
          << BBLUE << "=============================================================="
          << RESET << std::endl;

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
