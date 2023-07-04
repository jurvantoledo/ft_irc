#include "../../../include/Command.hpp"

joinCMD::joinCMD(Server& server): Command(server) {}

joinCMD::~joinCMD() {}

void	joinCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
	std::string	channel = args.front();
	args.pop();
	std::string	password;

	Channel* channel_ptr;
	bool	new_channel;

	if (strncmp(channel.c_str(), "#", 1))
		return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channel));
	
	if (args.size() > 1)
	{
		password = args.front();
		args.pop();
	}

	channel_ptr = this->_server.getChannel(channel);
	new_channel = !channel_ptr;
	if (!channel_ptr)
		channel_ptr = this->_server.addChannel(channel, client->getPassword());
	
	if (channel_ptr->getMaxUsers() && channel_ptr->getMaxUsers() >= channel_ptr->channelSize())
		return (void)client->queuePacket(ERR_CHANNELISFULL(client->getNickname(), channel));
	
	if (!channel_ptr->checkPassword(password))
		return (void)client->queuePacket(ERR_WRONGCHANPASS(client->getNickname(), channel));
	
	if (channel_ptr->isMember(client))
		return (void)client->queuePacket(RPL_JOIN(client->getNickname(), channel));
	
	if (channel_ptr->getInviteOnly() && !channel_ptr->isInvited(client))
		return (void)client->queuePacket(ERR_INVITEONLY(client->getNickname(), channel));

	channel_ptr->sendMessage(RPL_JOIN(client->getNickname(), channel), client);
	channel_ptr->addMember(client);
	// if (new_channel)
	// 	channel_ptr->addOperator(client);
}
