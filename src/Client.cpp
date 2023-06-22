#include "../include/Client.hpp"

Client::Client(int client_fd) : _client_fd(client_fd)
{
	std::cout << "Client constructor for Client with fd: # " << _client_fd << std::endl;
}

Client::~Client()
{
}