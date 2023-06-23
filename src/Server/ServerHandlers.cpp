#include "../../include/Server.hpp"

void	Server::addToPoll(int sockfd)
{
	struct pollfd client_poll;
	Client new_client(sockfd);

	client_poll.fd = sockfd;
	client_poll.events = POLLIN | POLLOUT;
	_pollfds.push_back(client_poll);

	// _clients.insert(std::pair<int, Client>(client_fd, new_client));
	std::cout << "[Server]: added the client # " << sockfd << std::endl;
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