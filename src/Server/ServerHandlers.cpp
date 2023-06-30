#include "../../include/Server.hpp"

bool	Server::handleData(int socket, Client* client)
{
	if (client->handleMessage())
	{
		client->receiveMessage();

		client->setDataToSend();
		return (true);
	}
	return (false);
}

int	Server::newClientConnection(int sockfd)
{
	int	client_fd = getAcceptedMan(sockfd);

	if (client_fd == -1)
	{
		std::cout << "Accept() function failed" << std::endl;
		return (1);
	}
	addToPoll(client_fd);
	return (0);
}

void	Server::processPacket(pollfd& pfds, Client* client)
{
	for (size_t j = 1; j < this->_pollfds.size(); j++)
	{
		 // Skip the current client
		if (pfds.fd != this->_pollfds[j].fd && client->hasDataToSend())
		{
			Client* targetClient = this->getClient(this->_pollfds[j].fd);
			client->sendMessage(targetClient->getSocket());
		}
	}
}