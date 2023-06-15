#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server
{
	private:
		int	_port;
		std::string _password;

	public:
		Server(int &port, std::string password);
		~Server();

		void	createSocket();
};

#endif