/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:34:17 by pscala            #+#    #+#             */
/*   Updated: 2025/05/28 08:00:15 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utils.hpp"

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
	const std::string &getChannelName() const;
	const std::set<Client *> &getClients() const;
};
