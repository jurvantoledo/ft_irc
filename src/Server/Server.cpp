#include "../../include/Server.hpp"

Server::Server(int &port, std::string password) : _port(port), _password(password), \
				_onlineClients(0), _pollfds(), _clients(), _commandHandlers(new CommandHandler(*this)) 
				{}

Server::~Server() 
{
	std::map<std::string, Channel*>::iterator ch_it;
	std::map<int, Client*>::iterator cl_it;

	delete _commandHandlers;
	close(this->_socket);

	for (ch_it = this->_channels.begin(); ch_it != this->_channels.end(); ch_it++)
		delete ch_it->second;
	
	for (cl_it = this->_clients.begin(); cl_it != this->_clients.end(); cl_it++)
		delete cl_it->second;
	
}

bool	Server::checkPassword(std::string password) { return this->_password == password; }

// void Server::broadcastMessage(pollfd& pfds, Client* client) {
//    	for (size_t j = 1; j < this->_pollfds.size(); j++)
// 	{
// 		// Skip the current client
// 		if (pfds.fd != this->_pollfds[j].fd && client->hasDataToSend() && !client->getIsCommand())
// 		{				
// 			Client* targetClient = this->getClient(this->_pollfds[j].fd);
// 			client->sendMessage(targetClient);
// 			client->clearDataToSend();
// 		}
// 	}
// }

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
		if (poll(this->_pollfds.data(), this->_pollfds.size(), -1) == -1)
		{
			std::cout << "Poll() failed" << std::endl;
			return ;
		}
		
		if (this->_pollfds[0].revents & POLLIN)
		{
			this->_pollfds[0].revents = 0;
			this->newClientConnection(sockfd);
		}

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			pollfd& pfds = this->_pollfds[i];
			client = this->getClient(pfds.fd);

			if (pfds.revents & POLLHUP)
			{
				this->getDisconnectedMan(client);
				this->removePollFlag(pfds, 0xFFFF);
				continue ;
			}
			
			// ready for getting incoming data
			if (pfds.revents & POLLIN)
			{
				if(!this->handleData(client))
					this->removePollFlag(pfds, POLLIN); // If incoming data fails delete pfd
			}

			// ready for sending outgoing data
			if (pfds.revents & POLLOUT)
			{
				if (client->processQueue())	// if queue is processed, remove POLLOUT
					this->removePollFlag(pfds, POLLOUT);
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
			if (client->getQueueSize())
				this->setPollFlag(*it, POLLOUT);
			++it;
		}
	}
}
