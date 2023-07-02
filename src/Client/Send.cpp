#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

bool	Client::hasDataToSend()
{
	return this->_dataToSend;
}

void Client::sendMessage(Client* client)
{
    std::string message = client->getPacket() + "\r\n";
    ssize_t bytesRead = send(this->_socket, message.c_str(), message.length(), 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Send() failed");
    }

    std::cout << "[Server]: [" << this->getNickname() << "]" << " Sent message to client #" << this->_socket << " " << message << std::endl;

    // Erase the sent message from the buffer
    this->clearDataToSend();
}
