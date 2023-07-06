#include "../../../include/Command.hpp"

nickCMD::nickCMD(Server& server) : Command(server) {}

nickCMD::~nickCMD() {}

void    nickCMD::ExecCommand(Client* client)
{
    std::string	nick = client->removeArgument();

	if (this->_server.getClientByName(nick))
		return (void)client->queuePacket(ERR_NICKNAMEINUSE(client->getNickname()));

	client->setNickname(nick);

	if (!client->getAuthenticatedUser() && !client->getUsername().empty())
		client->queuePacket(RPL_WELCOME(client->getNickname()));
}