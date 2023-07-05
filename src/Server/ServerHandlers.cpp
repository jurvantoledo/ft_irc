#include "../../include/Server.hpp"

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
		// this->handleDisconnect(client);
		return false;
	}
	return true;
}

int	Server::newClientConnection(int sockfd)
{
	int	client_fd = getAcceptedMan(sockfd);

	if (client_fd == -1)
	{
		std::cout << "Accept() function failed" << std::endl;
		return (1);
	}
	this->addToPoll(client_fd);
	return (0);
}

void	Server::processPacket(Client* client)
{
	try
	{
		this->_commandHandlers->Call(client, client->receiveMessage());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	Server::getDisconnectedMan(Client *client)
{
	std::map<std::string, Channel*>::iterator it;

	for (it = this->_channels.begin(); it != this->_channels.end(); it++)
		it->second->removeMember(client);
	
	this->removeClient(client->getSocket());

	std::cout << "[Server]: client fd #" << client->getSocket() << " disconnected" << std::endl;
}
