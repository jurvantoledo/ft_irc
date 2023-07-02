#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

bool	Client::handleMessage()
{
	char	buffer[MAX_BUFFER];

	memset(buffer, 0, sizeof(buffer));
	if (this->_buffer.find("\r\n") == std::string::npos)
	{
		ssize_t bytesRead = recv(this->_socket, buffer, MAX_BUFFER - 1, 0);
		if (bytesRead == -1 && errno == EAGAIN)
		{
			errno = 0;
			return false;
		}
		if (bytesRead == -1)
			throw Client::MessageException("Recv() failed");

		buffer[bytesRead] = '\0';
		this->_buffer += buffer;
	}
	bool messageComplete = this->_buffer.find("\r\n") != std::string::npos;

	// Set the flag if a complete message is received
	if (messageComplete)
		this->setDataToSend();
	
	return messageComplete;
}

std::string Client::receiveMessage()
{
	// Check for IRC PING command
    // if (this->_buffer.find("PING") != std::string::npos) {
    //     // Respond to PING with PONG
    //     std::string pingCommand = "PONG " + this->_buffer.substr(5) + "\r\n";
    //     send(socket, pingCommand.c_str(), pingCommand.length(), 0);
    //  }

	size_t pos = this->_buffer.find("\r\n");
	if (pos == std::string::npos)
	{
        throw std::runtime_error("Recv(): Called without CRLF present in buffer");
	}
	std::string packet = this->_buffer.substr(0, pos);

	std::cout << "[Server]: fd #" << _socket << " Received message from client #" << packet << std::endl;
    this->_buffer.erase(0, pos + 2);

    return packet;
}
