#include "../../include/Server.hpp"

void	Server::newClientConnection(int sockfd)
{
	try
	{
		int	client_fd = getAcceptedMan(sockfd);
		if (client_fd == -1)
		{
			std::cout << "Accept() function failed" << std::endl;
			return ;
		}

		this->addToPoll(client_fd);
	}
	catch(const std::exception& e)
	{
		return ;
	}
}

void	Server::getDisconnectedMan(Client *client)
{
	std::map<std::string, Channel*>::iterator it;

	for (it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		if (it->second->isMember(client))
		{
			it->second->removeMember(client);
		}
	}

	this->removeClient(client->getSocket());

	std::cout << "[Server]: client fd #" << client->getSocket() << " disconnected" << std::endl;
}

bool	Server::handleData(Client* client)
{
	try
	{
		if (!client->handleMessage())
			return true;
		this->processPacket(client);
	}
	catch(const std::exception& e)
	{
		this->getDisconnectedMan(client);
		return false;
	}
	return true;
}

void	Server::processPacket(Client* client)
{
	try
	{
		while (true) this->_commandHandlers->Call(client, client->receiveMessage());
	}
	catch(const std::exception& e) {}
}
