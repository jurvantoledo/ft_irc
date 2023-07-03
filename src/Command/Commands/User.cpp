#include "../../../include/Command.hpp"

userCMD::userCMD(Server& server): Command(server) {}

userCMD::~userCMD() {}

void    userCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
	std::string	username	= args.front();
    args.pop();
	std::string	realname	= args.front();
    args.pop();

	if (client->getAuthenticatedUser())
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));

	if (!this->_server.checkPassword(client->getPassword()))
		return (void)client->queuePacket(ERR_PASSWDMISMATCH(client->getNickname()));

	client->setUsername(username);
	client->setRealName(realname);

	if (client->getNickname().empty())
		return (void)client->queuePacket(ERR_NICKNAMENOTSET(client->getUsername()));

	client->setAuthenticatedUser();
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}