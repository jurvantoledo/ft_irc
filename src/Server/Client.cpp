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

Client*	Server::getClientByName(std::string& nickname)
{
	std::map<int, Client*>::iterator	it;

	if (!nickname.length())	// just in case a non-nicknamed user is queried
		return NULL;

	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getNickname() == nickname)
			return it->second;
		++it;
	}
	return NULL;
	// throw std::runtime_error("could not find client");
}