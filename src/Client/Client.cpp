#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

Client::Client(): _socket(-1),
				_nickname("UNKNOWN"), 
				_dataToSend(false),
				_authenticated(false) {}

Client::Client(int client_fd): 
				_socket(client_fd), 
				_nickname("UNKNOWN"), \
				_dataToSend(false), 
				_isCommand(false), 
				_authenticated(false) {}

Client::~Client() 
{
	close(this->_socket);
}

int		Client::getSocket() { return (this->_socket); }
void	Client::setSocket(int fd) { this->_socket = fd; }

// bool	Client::getIsCommand() { return (this->_isCommand); }
// void	Client::setIsCommand() { this->_isCommand = true; }
// void	Client::clearCommand() { this->_isCommand = false; }


// bool	Client::getDataToSend() { return (this->_dataToSend); }
// void	Client::setDataToSend() { this->_dataToSend = true; }
// void	Client::clearDataToSend() { this->_dataToSend = false; }

// std::string	Client::getPacket() { return (this->_packet); }
// void		Client::setPacket(std::string packet) { this->_packet = packet; }
