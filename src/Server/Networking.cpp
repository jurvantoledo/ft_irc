#include "../../include/Server.hpp"

const char* Server::SocketFailure::what(void) const throw()
{
	return "Failed to create socket.";
}

int		Server::createSocket() 
{
	/*
		int domain -> specifies communication domain We use AF_INET for processes connected by IPV6
		int type -> communication type - SOCK_STREAM: TCP(reliable, connection oriented)
		int protocol -> Protocol value for Internet Protocol(IP), which is 0. This is the same number 
					which appears on protocol field in the IP header of a packet.(man protocols for more details)
	*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		throw SocketFailure();
	}
	return sockfd;
}

void	Server::setSocketOptions(int sockfd)
{
	/*
		int socket -> Looks at the socket fd
		int level -> We set this as SOL_SOCKET to manipulate options at the sockets API level
		int option_name -> We set this to SO_REUSEADDR to allow re-using the same address and port combo on a socket.
							This is useful when binding to an address and port that were recently used by a closed socket..
							It helps avoid the "Address already in use" error. 
							To enable this option we set `int reuseaddr` to 1

		const void *option_value &&
		socklen_t option_len -> identify a buffer in which the value for the requested options are returned
	*/
	int reuseAddr = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) < 0)
	{
		std::cerr << "Failed to set socket option: SO_REUSEADDR." << std::endl;;
		return ;
	}
}

void	Server::bindSocket(int sockfd)
{
	// get the sockaddr_in struct
	sockaddr_in serverAddr;
	// set everything to 0
	memset(&serverAddr, 0, sizeof(serverAddr));
	
	// Set the Address Family
	serverAddr.sin_family = AF_INET;
	// The inet_addr() function shall convert the string pointed to by cp, in the standard IPv4 dotted decimal notation, to an integer value suitable for use as an Internet address.
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	// The htons function converts the unsigned short integer hostshort from host byte order to network byte order.
	serverAddr.sin_port = htons(_port);
	if (bind(sockfd, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		close(sockfd);
		std::cerr << "Failed to bind IP/port" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::setFcntl(int socket)
{
	if (fcntl(socket, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl() failed");
}	

int		Server::getAcceptedMan(int sockfd)
{
	sockaddr_in clientAddress;
	socklen_t clientAddresslen = sizeof(clientAddress);

	int new_sockfd = accept(sockfd, (struct sockaddr*)&clientAddress, &clientAddresslen);
	if (new_sockfd < 0)
	{
		throw SocketFailure();
	}
	return new_sockfd;
}

void	Server::setListen(int socket)
{
	if (listen(socket, 1) < 0)
	{
		close(socket);
		std::cerr << "Listen() failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Server listening on port: " << _port << std::endl;
}
