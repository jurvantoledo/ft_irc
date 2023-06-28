#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

Client::Client()
{
	_socket = this->getSocket();
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::Client(int client_fd) : _socket(client_fd)
{
	this->_dataToSend = false;
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::~Client() {}

int	Client::getSocket()
{
	return (this->_socket);
}

void	Client::setSocket(int fd)
{
	this->_socket = fd;
}

bool	Client::getDataToSend()
{
	return (this->_dataToSend);
}

void	Client::setDataToSend()
{
	this->_dataToSend = true;
}

void	Client::clearDataToSend()
{
	this->_dataToSend = false;
}
