#include "../../include/Server.hpp"

void	Server::addToPoll(int fd)
{
	struct pollfd client_poll;

	client_poll.fd = fd;
	client_poll.events = POLLIN | POLLHUP;
	this->_pollfds.push_back(client_poll);
	
	this->_clients.insert(std::pair<int, Client *>(fd, this->AddClient(fd)));
	std::cout << "[Server]: added the client # " << fd << std::endl;
}

void	Server::setPollFlag(pollfd &pfd, short events)
{

	pfd.events |= events;
}

void	Server::removePollFlag(pollfd &pfd, short event)
{
	pfd.events &= ~event;
}
