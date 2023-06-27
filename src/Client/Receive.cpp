#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

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

bool Client::receiveMessage(int socket)
{
	this->_buffer += handleMessage();
	// Check for IRC PING command
    // if (this->_buffer.find("PING") != std::string::npos) {
    //     // Respond to PING with PONG
    //     std::string pingCommand = "PONG " + this->_buffer.substr(5) + "\r\n";
    //     send(socket, pingCommand.c_str(), pingCommand.length(), 0);
    //  }

	size_t pos = this->_buffer.find("\r\n");
	if (pos != std::string::npos)
	{
		std::string message = this->_buffer.substr(0, pos);
		this->_buffer.erase(0, pos + 2);

		std::cout << "Server with fd # " << socket << " Received message from client # " << message << std::endl;
        return (true);
	}
    return (false);
}