#include "Server.hpp"

Client*	Server::AddClient(int fd)
{
	Client *new_client;

	new_client = new Client(fd);
    new_client->setSocket(fd);

	return new_client;
}

Client*	Server::getClient(int fd)
{
	return (this->_clients.at(fd));
}