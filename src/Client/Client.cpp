#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

Client::Client()
{
	_socket = this->getSocket();
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::Client(int client_fd) : _socket(client_fd)
{
	std::cout << "Client constructor for Client with fd: # " << _socket << std::endl;
}

Client::~Client()
{
}

std::string	Client::handleMessage()
{
	char	buffer[MAX_BUFFER];
	std::string res;

	memset(buffer, 0, sizeof(buffer));

	ssize_t bytesRead = recv(this->_socket, buffer, MAX_BUFFER - 1, 0);
	if (bytesRead == 0 )
	{
		throw MessageException("Recv() disconnect noticed");
	}
	else if (bytesRead == -1)
	{
		throw MessageException("Recv() failure");
	}

	return res += buffer;
}

void Client::receiveMessage(int socket)
{
	this->_buffer += handleMessage();
	// Check for IRC PING command
    if (this->_buffer.find("PING") != std::string::npos) {
        // Respond to PING with PONG
        std::string pingCommand = "PONG " + this->_buffer.substr(5) + "\r\n";
        send(socket, pingCommand.c_str(), pingCommand.length(), 0);
     }

	size_t pos = this->_buffer.find("\r\n");
	if (pos != std::string::npos)
	{
		std::string message = this->_buffer.substr(0, pos);
		this->_buffer.erase(0, pos + 2);

		std::cout << "fd: " << socket << " Received message from client # " << message << std::endl;
	}
}

int	Client::getSocket()
{
	return (this->_socket);
}

void	Client::setSocket(int fd)
{
	this->_socket = fd;
}
