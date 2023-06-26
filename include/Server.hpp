#ifndef SERVER_H
#define SERVER_H
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <map>
#include "Client.hpp"

#define MAX_BUFFER 1024
#define MAX_ONLINE 10

class Server
{
	private:
		int	_socket; 
		int	_port;
		std::string _password;
		int	_onlineClients;
    	std::vector<pollfd> _pollfds;
		std::map<int, Client *> _clients;

	public:
		Server(int &port, std::string password);
		~Server();

		void	stayConnectedMan();
		int		createSocket();
		void	setSocketOptions(int sockfd);
		void	bindSocket(int sockfd);
		int		newClientConnection(int sockfd);
		Client	*getClient(int fd);
		void	addToPoll(int fd);
		int		getAcceptedMan(int sockfd);
		void	handleData(int socket, Client* client);

		class SocketFailure : public std::exception {
			const char *what() const throw();
		};
};

#endif