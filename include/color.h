/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:12:51 by kasingh           #+#    #+#             */
/*   Updated: 2025/05/26 16:29:30 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h> // inet_ntoa() si tu veux convertir adresse IP
#include <cstdlib>
#include <cstdlib>      // exit, atoi, strtol
#include <cstring>      // memset (pour struct sockaddr_in), strerror
#include <errno.h>      // errno pour messages d’erreur système
#include <fcntl.h>      // fcntl() pour mettre le socket en non-bloquant
#include <iostream>     // std::cout, std::cerr
#include <netinet/in.h> // sockaddr_in, htons(), htonl(), INADDR_ANY
#include <string>       // std::string
#include <sys/epoll.h>  // poll() et struct pollfd
#include <sys/socket.h> // socket(), bind(), listen(), setsockopt()
#include <sys/types.h>  // types systèmes : socket, bind, etc.
#include <unistd.h>     // close()
#include <vector>
#include <set>
#include <sstream>


// Reset
#define RESET "\033[0m"

// Regular Colors
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

// Bold Colors
#define BBLACK "\033[1;30m"
#define BRED "\033[1;31m"
#define BGREEN "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE "\033[1;34m"
#define BMAGENTA "\033[1;35m"
#define BCYAN "\033[1;36m"
#define BWHITE "\033[1;37m"

// Underline Colors
#define UBLACK "\033[4;30m"
#define URED "\033[4;31m"
#define UGREEN "\033[4;32m"
#define UYELLOW "\033[4;33m"
#define UBLUE "\033[4;34m"
#define UMAGENTA "\033[4;35m"
#define UCYAN "\033[4;36m"
#define UWHITE "\033[4;37m"

// Background Colors
#define ON_BLACK "\033[40m"
#define ON_RED "\033[41m"
#define ON_GREEN "\033[42m"
#define ON_YELLOW "\033[43m"
#define ON_BLUE "\033[44m"
#define ON_MAGENTA "\033[45m"
#define ON_CYAN "\033[46m"
#define ON_WHITE "\033[47m"
#define ON_LIGHT_GRAY "\033[48;5;250m" // Gris clair
#define ON_DARK_GRAY "\033[48;5;240m"  // Gris foncé
