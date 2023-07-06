#include "../../../include/Command.hpp"

privMsgCMD::privMsgCMD(Server& server): Command(server) {}

privMsgCMD::~privMsgCMD() {}

void	privMsgCMD::toChannel(Client* client, std::string& target)
{
	Channel*	channel = this->_server.getChannel(target);
	
	if (!channel)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), target));

	if (!channel->isMember(client))
		return (void)client->queuePacket(ERR_CANNOTSENDTOCHAN(client->getNickname(), target));

	channel->sendMessage(RPL_PRIVMSG(client->getNickname(), target, client->getRemainingArguments()), client);
}

void	privMsgCMD::toClient(Client* client, std::string& target)
{
	Client*	client_ptr = this->_server.getClientByName(target);

	if (!client_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), target));
	client_ptr->queuePacket(RPL_PRIVMSG(client->getNickname(), target, client->getRemainingArguments()));
}

void    privMsgCMD::ExecCommand(Client* client)
{
    std::string	target = client->removeArgument();
	if ((char)target[0] == '#')
	{ 
		this->toChannel(client, target);
	}
	else
		this->toClient(client, target);
}
