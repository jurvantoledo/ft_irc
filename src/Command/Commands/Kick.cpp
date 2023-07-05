#include "../../../include/Command.hpp"

kickCMD::kickCMD(Server& server): Command(server) {}

kickCMD::~kickCMD() {}

void    kickCMD::ExecCommand(Client* client, Arguments& args)
{
    std::string user = args.removeArgument();
    std::string channelName = args.removeArgument();

    Channel* channel = this->_server.getChannel(channelName);
    Client* user_ptr = this->_server.getClientByName(user);

    if (!channel)
        return ;
    if (!user_ptr)
        return ;
    if (!channel->isOperator(client))
        return ;
    if (!channel->isMember(user_ptr))
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channelName));
    
    channel->removeMember(user_ptr);
}