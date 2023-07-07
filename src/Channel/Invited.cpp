#include "../../include/Channel.hpp"
#include "../../include/Client.hpp"

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

	for (it = this->_invited.begin(); it != this->_invited.end();)
	{
		if (*it == client)
			it = this->_invited.erase(it);
		else
			it++;
	}
}
