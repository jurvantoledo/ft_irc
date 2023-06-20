#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 4096

class Server
{
	private:
		int	_port;
		std::string _password;

	public:
		Server(int &port, std::string password);
		~Server();

		void	runSocket();
		int		createSocket();
		void	setSocketOptions(int sockfd);
		void	bindSocket(int sockfd);
		void	listenForConnect(int sockfd);
		int		acceptConnection(int sockfd);
};

#endif