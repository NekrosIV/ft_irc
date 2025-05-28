/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:38:52 by pscala            #+#    #+#             */
/*   Updated: 2025/05/27 23:46:22 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "color.hpp"

typedef struct s_parsed_command
{
	std::string prefix;
	std::string command;
	std::vector<std::string> params;
}	t_parsed_command;

t_parsed_command parseIrcCommand(const std::string line);
void CheckSyscall(const int res, const std::string& context);
