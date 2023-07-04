#ifndef CHANNEL_H

#define CHANNEL_H
#include <iostream>

#include "Client.hpp"
#include "Replies.hpp"


class Channel
{
	private:
		std::string	_name;
		std::string	_topic;
		std::string	_password;

		std::vector<Client*>	_members;
		std::vector<Client*>	_operators;
		std::vector<Client*>	_invited;

		bool	_invite_only;
		bool	_topic_ops;
		size_t	_max_users_channel;

	public:
		Channel(std::string& channel, std::string& password);
		~Channel();

		void	setTopic(std::string topic);
		void	setPassword(std::string password);
		void	setInviteOnly(bool invite_only);
		void	setTopicOps(bool topic_ops);
		void	setMaxUsers(size_t limit);

		std::string	getTopic() const;
		bool		getInviteOnly() const;
		bool		getTopicOps() const;
		size_t		getMaxUsers() const;
		bool		checkPassword(std::string password) const;

		std::string	getModes();

		void	sendMessage(std::string message, Client* client);

		bool	isMember(Client *client);
		bool	isOperator(Client *client);
		bool	isInvited(Client* client);

		void	addMember(Client* client);
		void	addOperator(Client* client);
		void	addInvited(Client* client);

		void	removeMember(Client* client);
		void	removeOperator(Client* client);
		void	removeInvited(Client* client);

		size_t	channelSize();
};

#endif