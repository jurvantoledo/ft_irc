#include "../include/Server.hpp"

int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>"<< std::endl;
		return (EXIT_FAILURE);
	}
	int port = atoi(argv[1]);

	try
	{	
		Server server(port, argv[2]);

		server.runServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
