#include "../../../include/Command.hpp"

passCMD::passCMD(Server& server): Command(server) {}

passCMD::~passCMD() {}

void    passCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
	std::string password = args.front();
    args.pop();
	
	if (client->getAuthenticatedUser())
	{
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));
	}
	
	client->setPassword(password);
}
