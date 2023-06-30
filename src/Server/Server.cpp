#include "../../include/Server.hpp"

Server::Server(int &port, std::string password) : _port(port), _password(password), \
				_onlineClients(0), _pollfds(), _clients()
{
	std::cout << "Server constructor is called\n" << std::endl;
}

Server::~Server() {}

void	Server::stayConnectedMan()
{
	Client* client;

	int sockfd = createSocket();
	if (sockfd == -1)
	{
		std::cerr << "Failed to create socket." << std::endl;
		exit(EXIT_FAILURE);
	}
	setSocketOptions(sockfd);
	bindSocket(sockfd);
 
	if (listen(sockfd, 5) < 0)
	{
		close(sockfd);
		std::cerr << "Listen() failed" << std::endl;
		exit(EXIT_FAILURE);
	}

    std::cout << "Server listening on port" << " " << _port << std::endl;

	struct	pollfd server_poll;
	server_poll.fd = sockfd;
	server_poll.events = POLLIN;

	this->_pollfds.push_back(server_poll);
	while (1)
	{
		int	active = poll(&this->_pollfds[0], this->_pollfds.size(), -1);
		if (active == -1)
		{
			std::cout << "Poll() failed" << std::endl;
			return ;
		}
		
		if (this->_pollfds[0].revents & POLLIN)
		{
			this->_pollfds[0].revents = 0;
			if (newClientConnection(sockfd) != 0)
			{
				close(sockfd);
				continue ;
			}
		}

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			pollfd& pfds = this->_pollfds[i];
			client = this->getClient(pfds.fd);
			if (pfds.revents & POLLIN)
			{
				if(!this->handleData(pfds.fd, client))
					this->removePollFlag(pfds, POLLIN);
			}

			if (pfds.revents & POLLOUT)
			{
				if (client->hasDataToSend())
				{
					this->processPacket(pfds, client);
					this->removePollFlag(pfds, POLLOUT);
				}
				// Clear the flag once the data is sent
				client->clearDataToSend();
			}
			pfds.revents = 0;
		}
		std::vector<pollfd>::iterator it = this->_pollfds.begin() + 1;
		while (it != this->_pollfds.end())
		{
			if (!it->events)
				it = this->_pollfds.erase(it);
			else
				it++;
		}
		
		it = this->_pollfds.begin() + 1;
		while (it != this->_pollfds.end())
		{
			client = this->getClient(it->fd);
			if (client->hasDataToSend())
			{
				this->setPollFlag(*it, POLLOUT);
			}
			it++;
		}
		
	}
	close(sockfd);
}
