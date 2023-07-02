#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

Client::Client(): _socket(-1),
				_nickname("UNKNOWN"), 
				_dataToSend(false),
				_already_exists(false)
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::Client(int client_fd): 
				_socket(client_fd), 
				_nickname("UNKNOWN"), \
				_dataToSend(false), 
				_isCommand(false), 
				_already_exists(false)
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::~Client() 
{
	close(this->_socket);
}

// Getters
int		Client::getSocket() { return (this->_socket); }
bool	Client::getDataToSend() { return (this->_dataToSend); }
bool	Client::getIsCommand() { return (this->_isCommand); }
std::string	Client::getPacket() { return (this->_packet); }

// Setters
void	Client::setSocket(int fd) { this->_socket = fd; }
void	Client::setPacket(std::string packet) { this->_packet = packet; }
void	Client::setDataToSend() { this->_dataToSend = true; }
void	Client::setIsCommand() { this->_isCommand = true; }
void	Client::clearDataToSend() { this->_dataToSend = false; }
void	Client::clearCommand() { this->_isCommand = false; }
