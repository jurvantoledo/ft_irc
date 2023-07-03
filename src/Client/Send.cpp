#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

size_t	Client::getQueueSize()
{
	return this->_queue.size();
}

bool	Client::processQueue()
{
	while (this->_queue.size() && this->sendPacket()); // try to process all packets
	return this->_queue.size() == 0;
}

bool	Client::sendPacket()
{
	ssize_t			sent;
	std::string&	packet = this->_queue.front();

	if (packet.size())
	{
		sent = send(this->_socket, packet.data(), packet.length(), 0);
		if ((sent == -1 && errno == EAGAIN) || sent == 0)
		{
			errno = 0;
			return false;
		}
		if (sent == -1)
			throw MessageException("sendPacket() -> Send() failure and errno != EAGAIN");

		packet.erase(0, sent);
	}

	if (packet.size())
		return false;

	this->_queue.pop();
	return true;
}

void	Client::queuePacket(std::string packet)
{
    std::cout << "[Server]: [" << this->getNickname() << "]" << " Sent message to client #" << packet << std::endl;
	std::string	complete = packet + "\r\n";
	this->_queue.push(complete);
}