/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:34:17 by pscala            #+#    #+#             */
/*   Updated: 2025/05/29 06:48:07 by pscala           ###   ########.fr       */
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

	int _maxMembers;

	bool _isPrivate;
	bool _isSecret;
	bool _requierPass;
	bool _isInviteOnly;

	std::set<Client *> _members;
	std::set<Client *> _operators;
	std::set<Client *> _bannedMembers;
	std::set<Client *> _invitedMembers;

  public:
	Channel(const std::string name);
	~Channel();
	void AddClient(const Client *newMember);
	void RemoveClient(const Client *member);
	void RemoveOperator(const Client *op);
	const std::string &getChannelName() const;
	const std::set<Client *> &getClients() const;
};
