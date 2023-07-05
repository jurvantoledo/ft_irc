#include "../../../include/Command.hpp"

inviteCMD::inviteCMD(Server& server): Command(server) {}

inviteCMD::~inviteCMD() {}

void    inviteCMD::ExecCommand(Client* client, Arguments& args)
{
    std::string user = args.removeArgument();
    std::string channel = args.removeArgument();

    Client* user_ptr = this->_server.getClientByName(user);
    Channel* channel_ptr = this->_server.getChannel(channel);

    if (!channel_ptr)
        return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channel));
    if (!user_ptr)
        return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), user));
    if (channel_ptr->getInviteOnly() && !channel_ptr->isOperator(client))
        return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel));
    
    channel_ptr->addInvited(user_ptr);
    user_ptr->queuePacket(RPL_INVITE(client->getNickname(), user, channel));
}