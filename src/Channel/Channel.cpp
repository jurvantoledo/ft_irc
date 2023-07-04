#include "../../include/Channel.hpp"

Channel::Channel(std::string& channel, std::string& password)
{
	std::cout << "Channel constructed" << std::endl;
}

Channel::~Channel()
{
}

// Getters
std::string	Channel::getTopic()								const { return (this->_topic); }
bool		Channel::getTopicOps()							const { return (this->_topic_ops); }
bool		Channel::getInviteOnly()						const { return (this->_invite_only); }
bool		Channel::checkPassword(std::string password)	const { return (this->_password == password); }
size_t		Channel::getMaxUsers() 							const { return (this->_max_users_channel); }

std::string	Channel::getModes() 
{
	std::string	modes("+n");

	if (this->_invite_only)			modes += 'i';
	if (!this->_password.empty())	modes += 'k';
	if (this->_topic_ops)			modes += 't';
	if (this->_max_users_channel)	modes += 'l';

	return modes;
}

// Setters
void	Channel::setTopic(std::string topic) 		{ this->_topic = topic; }
void	Channel::setTopicOps(bool topic_ops)		{ this->_topic_ops = topic_ops; }
void	Channel::setInviteOnly(bool invite_only)	{ this->_invite_only = invite_only; }
void	Channel::setMaxUsers(size_t limit)			{ this->_max_users_channel = limit; }
void	Channel::setPassword(std::string password)	{ this->_password = password; }