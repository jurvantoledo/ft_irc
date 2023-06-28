#include "../../include/Server.hpp"
#include "../../include/Client.hpp"

Client*	Server::getClient(int fd)
{
	return (this->_clients.at(fd));
}

bool	Server::handleData(int socket, Client* client)
{
	
	if (client->handleMessage())
	{
		client->receiveMessage(client->getSocket());

		client->setDataToSend();
		return (true);
	}
	return (false);
}

void	Server::addToPoll(int fd)
{
	struct pollfd client_poll;
	Client *new_client;

	new_client = new Client(fd);

	client_poll.fd = fd;
	client_poll.events = POLLIN | POLLHUP;
	this->_pollfds.push_back(client_poll);
	
	this->_clients.insert(std::pair<int, Client *>(client_poll.fd, new_client));
	std::cout << "[Server]: added the client # " << fd << std::endl;
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