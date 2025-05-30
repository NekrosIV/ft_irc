/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:34:17 by pscala            #+#    #+#             */
/*   Updated: 2025/05/30 04:26:23 by kasingh          ###   ########.fr       */
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
	std::string _password;

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
	void AddClient(Client *newMember);
	void RemoveClient(Client *member);
	void RemoveOperator(Client *op);
	void addOperator(Client *client);
	void invite(Client *client);
	void ban(Client *client);
	bool isMember(Client *client) const;
	bool isOperator(Client *client) const;
	bool isInvited(Client *client) const;
	bool isBanned(Client *client) const;
	void setPassword(const std::string &pass);
	void setLimit(int limit);
	void setTopic(const std::string &topic);
	const std::string &getTopic() const; 
	const std::string &getChannelName() const;
	const std::set<Client *> &getClients() const;
};
