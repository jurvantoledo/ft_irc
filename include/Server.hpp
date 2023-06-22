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

#define MAX_BUFFER 4096
#define MAX_ONLINE 10

class Server
{
	private:
		int	_port;
		std::string _password;
		int	_onlineClients;
    	std::vector<pollfd> _pollfds;
		std::map<int, Client> _clients;

	public:
		Server(int &port, std::string password);
		~Server();

		void	stayConnectedMan();
		int		createSocket();
		void	setSocketOptions(int sockfd);
		void	bindSocket(int sockfd);
		void	listenForConnect(int sockfd);
		int		newClientConnection(int sockfd);
		void	addClient(int client_fd);
		void	addToPoll(int sockfd);
		int		getAcceptedMan(int sockfd);
		void	handleMessage(int sockfd, const std::string &message);
		std::string	receiveMessage(int sockfd);

		class SocketFailure : public std::exception {
			const char *what() const throw();
		};
};

#endif