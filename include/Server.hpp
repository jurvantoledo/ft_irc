#ifndef SERVER_H
#define SERVER_H
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <map>
#include "Client.hpp"
#include "Channel.hpp"

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
		std::map<std::string, Channel*> _channels;

	public:
		Server(int &port, std::string password);
		~Server();

		void		stayConnectedMan();

		Channel*	addChannel(std::string channel, std::string password);
		Channel*	getChannel(std::string channel);
		void		removeChannel(std::string channel);

		class SocketFailure : public std::exception {
			const char *what() const throw();
		};
	
	private:
		int		createSocket();
		void	bindSocket(int sockfd);
		int		newClientConnection(int sockfd);
		int		getAcceptedMan(int sockfd);
		bool	handleData(int socket, Client* client);
		void	setSocketOptions(int sockfd);

		void	processPacket(pollfd& pfds, Client* client);

		Client*	AddClient(int fd);
		Client*	getClient(int fd);
		Client*	removeClient(int fd);

		void	addToPoll(int fd);
		void	setPollFlag(pollfd &pfd, short events);
		void	removePollFlag(pollfd &pfd, short events);
};

#endif