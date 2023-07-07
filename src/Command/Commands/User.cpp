#include "../../../include/Command.hpp"

userCMD::userCMD(Server& server): Command(server) {}

userCMD::~userCMD() {}

void    userCMD::ExecCommand(Client* client)
{
	std::string	username	= client->removeArgument();
	std::string	mode		= client->removeArgument();
	std::string	_			= client->removeArgument();
	std::string	realname	= client->removeArgument();

	if (client->getAuthenticatedUser())
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));

	if (!this->_server.checkPassword(client->getPassword()))
		return (void)client->queuePacket(ERR_PASSWDMISMATCH(client->getNickname()));

	client->setUsername(username);
	client->setRealName(realname);

	if (client->getNickname().empty())
	{
		client->eraseArgument();
		return (void)client->queuePacket(ERR_NICKNAMENOTSET(client->getUsername()));
	}

	client->setAuthenticatedUser();
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}