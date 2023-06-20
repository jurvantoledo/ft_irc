#include "../include/Server.hpp"

Server::Server(int &port, std::string password) : _port(port), _password(password)
{
	std::cout << port << " " << password << std::endl;
}

Server::~Server()
{
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
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// The htons function converts the unsigned short integer hostshort from host byte order to network byte order.
	serverAddr.sin_port = htons(_port);
	if (bind(sockfd, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		close(sockfd);
		std::cerr << "Failed to bind IP/port" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::listenSocket(int sockfd)
{
	if (listen(sockfd, 5) < 0)
	{
		close(sockfd);
		std::cerr << "Failed to listen to socket" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int		Server::acceptConnection(int sockfd)
{
	int	new_sockfd;

	new_sockfd = accept(sockfd, nullptr, nullptr);
	if (new_sockfd < 0)
	{	
		close(sockfd);
		std::cerr << "Failed to accept connection." << std::endl;
		exit(EXIT_FAILURE);
	}

	return new_sockfd;
}

void	Server::createSocket() 
{
	char buffer[1024] = { 0 };

	/*
		int domain -> specifies communication domain We use AF_INET for processes connected by IPV6
		int type -> communication type - SOCK_STREAM: TCP(reliable, connection oriented)
		int protocol -> Protocol value for Internet Protocol(IP), which is 0. This is the same number 
					which appears on protocol field in the IP header of a packet.(man protocols for more details)
	*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		std::cerr << "Failed to create socket." << std::endl;
		return ;
	}
	
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
	setSocketOptions(sockfd);

	bindSocket(sockfd);

	listenSocket(sockfd);

    std::cout << "Server listening on port" << " " << _port << std::endl;

	int new_sockfd = acceptConnection(sockfd);
	read(new_sockfd, buffer, 1024);
    printf("%s\n", buffer);
	std::string hello = "wtf bruh";
    send(new_sockfd, NULL, 1000, 0);
    printf("Hello message sent\n");

	close(new_sockfd);
	shutdown(sockfd, SHUT_RDWR);
}