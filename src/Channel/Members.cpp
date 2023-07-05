#include "../../include/Channel.hpp"
#include "../../include/Client.hpp"

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