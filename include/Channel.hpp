/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:34:17 by pscala            #+#    #+#             */
/*   Updated: 2025/05/26 05:29:42 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "color.h"

class	Client;

class Channel
{
  private:
	std::string _name;
	std::string _topic;

	std::set<Client *> _members;
	std::set<Client *> _operators;

  public:
	Channel(const std::string name);
	~Channel();
	void AddClient(const Client *newMember);
	void RemoveClient(const Client *member);
	void RemoveOperator(const Client *op);
};
