#include "../../../include/Command.hpp"

passCMD::passCMD(Server& server): Command(server) {}

passCMD::~passCMD() {}

void    passCMD::ExecCommand(Client* client)
{
	std::string password = client->removeArgument();
	
	if (client->getAuthenticatedUser())
	{
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));
	}
	
	client->setPassword(password);
}
