#include <iostream>

int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>"<< std::endl;
		return (EXIT_FAILURE);
	}
	int port = atoi(argv[1]);

	std::cout << "lol" << std::endl;
	return (0);
}
