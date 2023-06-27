#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

// void Client::receiveMessage(int socket)
// {
// 	this->_buffer += handleMessage();
// 	// Check for IRC PING command
//     if (this->_buffer.find("PING") != std::string::npos) {
//         // Respond to PING with PONG
//         std::string pingCommand = "PONG " + this->_buffer.substr(5) + "\r\n";
//         send(socket, pingCommand.c_str(), pingCommand.length(), 0);
//      }

// 	size_t pos = this->_buffer.find("\r\n");
// 	if (pos != std::string::npos)
// 	{
// 		std::string message = this->_buffer.substr(0, pos);
// 		this->_buffer.erase(0, pos + 2);

// 		std::cout << "fd: " << socket << " Received message from client # " << message << std::endl;
// 	}
// }
