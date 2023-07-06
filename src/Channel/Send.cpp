#include "../../include/Channel.hpp"

void	Channel::sendMessage(std::string message, Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = this->_members.begin(); it != this->_members.end(); it++)
	{
		if (*it != client)
			(*it)->queuePacket(message);
	}
}
