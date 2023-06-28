#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

bool	Client::hasDataToSend()
{
	if (this->_dataToSend)
	{
		return (true);
	}
	return (false);
}

void Client::sendMessage(int socket)
{

    std::size_t pos = this->_buffer.find("\r\n");

    if (pos == std::string::npos) {
        throw Client::MessageException("sendMessage(): Called without CRLF present in buffer");
    }

    std::string message = this->_buffer.substr(0, pos);
    ssize_t bytesRead = send(socket, message.c_str(), message.length(), 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Send() failed");
    }

    std::cout << "[Server]: fd #" << _socket << " Sent message to client #" << message << std::endl;
    
    // Erase the sent message from the buffer
    this->_buffer.erase(0, pos + 2);
}
