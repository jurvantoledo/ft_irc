#include "../../../include/Command.hpp"

privMsgCMD::privMsgCMD(Server& server): Command(server) {}

privMsgCMD::~privMsgCMD() {}

void	privMsgCMD::toClient(Client* client, std::string& target, std::queue<std::string> args)
{
	Client*	client_ptr = this->_server.getClientByName(target);

	if (!client_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), target));

	client_ptr->queuePacket(RPL_PRIVMSG(client->getNickname(), target, args.front()));
}

void    privMsgCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string	target = args.front();
    args.pop();

	this->toClient(client, target, args);
}
