#include "../../include/Channel.hpp"

bool	Channel::isMember(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_members.begin(); it != this->_members.end(); it++)
	{
		if (*it == client)
			return true;
	}
	return false;
}

void	Channel::addMember(Client *client)
{
	if (this->isMember(client))
		return ;
	this->_members.push_back(client);
	client->queuePacket(RPL_JOIN(client->getNickname(), this->_name));
	client->queuePacket(RPL_MODE(client->getNickname(), this->_name, this->getModes()));
	client->queuePacket(RPL_TOPIC(client->getNickname(), this->_name, this->getTopic()));
}

void	Channel::removeMember(Client *client)
{
	std::vector<Client*>::iterator it;

	if (this->isMember(client))
	{
		return ;
	}
	
	this->sendMessage(RPL_LEAVE(client->getNickname(), this->_name), client);

	for (it = this->_members.begin(); it != this->_members.end(); it++)
	{
		if (*it == client)
			it = this->_members.erase(it);
		else
			it++;
	}
}

void	Channel::addOperator(Client* client)
{
	if (!this->isMember(client) && !this->isOperator(client))
		this->_operators.push_back(client);
}

bool	Channel::isOperator(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_operators.begin(); it != this->_operators.end(); it++)
	{
		if (*it == client)
			return true;
	}
	return false;
}

void	Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_operators.begin(); it != this->_operators.end(); it++)
	{
		if (*it == client)
			it = this->_operators.erase(it);
		else
			it++;
	}
}

void	Channel::addInvited(Client* client)
{
	if (!this->isMember(client) && !this->isInvited(client))
		this->_invited.push_back(client);
}

bool	Channel::isInvited(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_invited.begin(); it != this->_invited.end(); it++)
	{
		if (*it == client)
			return true;
	}
	return false;
}

void	Channel::removeInvited(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_invited.begin(); it != this->_invited.end(); it++)
	{
		if (*it == client)
			it = this->_invited.erase(it);
		else
			it++;
	}
}

size_t	Channel::channelSize() { return this->_members.size(); }