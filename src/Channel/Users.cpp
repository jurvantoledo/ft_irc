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

}

void	Channel::addOperator(Client* client)
{
	return ;
}

bool	Channel::isOperator(Client* client)
{
	return false ;
}

void	Channel::removeOperator(Client* client)
{
	return ;
}

void	Channel::addInvited(Client* client)
{
	return ;
}

bool	Channel::isInvited(Client* client)
{
	return false ;
}

void	Channel::removeInvited(Client* client)
{
	return ;
}

size_t	Channel::channelSize() { return this->_members.size(); }