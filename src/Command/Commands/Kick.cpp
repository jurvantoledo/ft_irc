#include "../../../include/Command.hpp"

kickCMD::kickCMD(Server& server): Command(server) {}

kickCMD::~kickCMD() {}

void    kickCMD::ExecCommand(Client* client)
{
    std::string channelName = client->removeArgument();
    std::string user = client->removeArgument();

    Channel* channel = this->_server.getChannel(channelName);
    Client* user_ptr = this->_server.getClientByName(user);

    if (!channel)
		  return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channelName));
    if (!user_ptr)
		  return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channelName));
    if (!channel->isOperator(client))
		  return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
    if (!channel->isMember(user_ptr))
		  return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channelName));
    
    channel->removeMember(user_ptr);
}