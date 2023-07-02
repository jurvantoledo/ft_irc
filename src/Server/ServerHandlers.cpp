#include "../../include/Server.hpp"

bool	Server::handleData(int socket, Client* client)
{
	if (client->handleMessage())
	{
		std::string message = client->receiveMessage();
		this->processPacket(client, message);

        client->setDataToSend();
	
		return (true);
	}
	// this->removeClient(socket);
	return (false);
}

int	Server::newClientConnection(int sockfd)
{
	int	client_fd = getAcceptedMan(sockfd);

	if (client_fd == -1)
	{
		std::cout << "Accept() function failed" << std::endl;
		return (1);
	}
	this->addToPoll(client_fd);
	return (0);
}

void	Server::processPacket(Client* client, std::string& message)
{
	try
	{
		this->_commandHandlers->Call(client, message);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
