#include "../../../include/Command.hpp"

joinCMD::joinCMD(Server& server): Command(server) {}

joinCMD::~joinCMD() {}

void	joinCMD::ExecCommand(Client* client)
{
	std::string	channelName = client->removeArgument();
	std::string	password;
	Channel* channel;
	bool	new_channel;

	if ((char)channelName[0] != '#')
		return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channelName));
	
	if (client->queueSize())
		password = client->removeArgument();

	channel = this->_server.getChannel(channelName);
	if (channel == NULL)
		new_channel = true;

	if (!channel)
		channel = this->_server.addChannel(channelName, client->getPassword());
	
	if (channel->getMaxUsers() > 0 && channel->channelSize() >= channel->getMaxUsers())
		return (void)client->queuePacket(ERR_CHANNELISFULL(client->getNickname(), channelName));
	
	if (!channel->checkPassword(password))
		return (void)client->queuePacket(ERR_WRONGCHANPASS(client->getNickname(), channelName));
	
	if (channel->isMember(client))
		return (void)client->queuePacket(RPL_JOIN(client->getNickname(), channelName));
	
	if (channel->getInviteOnly() && !channel->isInvited(client))
		return (void)client->queuePacket(ERR_INVITEONLY(client->getNickname(), channelName));

	channel->sendMessage(RPL_JOIN(client->getNickname(), channelName), client);
	channel->addMember(client);
	if (new_channel)
		channel->addOperator(client);
}
