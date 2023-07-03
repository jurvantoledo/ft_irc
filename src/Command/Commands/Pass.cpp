#include "../../../include/Command.hpp"

passCMD::passCMD(Server& server): Command(server) {}

passCMD::~passCMD() {}

void    passCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
	std::string password = args.front();
    args.pop();
	
	if (client->getAuthenticatedUser())
	{
		std::cout << "[Client]: " << "[" << client->getNickname() << "]" << " already exists!" << std::endl;
        client->clearDataToSend(); // Clear any pending data to send
        client->setDataToSend(); // Set the data to send flag
		return ;
	}
	
	client->setPassword(password);
}
