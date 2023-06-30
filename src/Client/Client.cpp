#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

Client::Client() : _socket(-1)
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::Client(int client_fd) : _socket(client_fd)
{
	this->_dataToSend = false;
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::~Client() {}

// Getters
int		Client::getSocket() { return (this->_socket); }
bool	Client::getDataToSend() { return (this->_dataToSend); }

// Setters
void	Client::setSocket(int fd) { this->_socket = fd; }
void	Client::setDataToSend() { this->_dataToSend = true; }
void	Client::clearDataToSend() { this->_dataToSend = false; }
