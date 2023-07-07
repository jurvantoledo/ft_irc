#include "../../include/Channel.hpp"
#include "../../include/Client.hpp"

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

	for (it = this->_operators.begin(); it != this->_operators.end();)
	{
		if (*it == client)
			it = this->_operators.erase(it);
		else
			it++;
	}
}
