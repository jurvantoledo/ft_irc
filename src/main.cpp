#include "../include/Server.hpp"

int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>"<< std::endl;
		return (EXIT_FAILURE);
	}
	int port = atoi(argv[1]);

	Server server(port, argv[2]);

	server.runSocket();
	return (0);
}
