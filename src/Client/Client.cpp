#include "../../include/Client.hpp"

Client::Client()
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::Client(int client_fd) : _socket(client_fd)
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::~Client()
{
}

void	Client::handleMessage(int socket, std::string packet)
{

}

std::string Client::receiveMessage()
{

}

void	Client::setSocket(int fd)
{
	this->_socket = fd;
}

int	Client::getSocket()
{
	return (this->_socket);
}
