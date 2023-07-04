#include "../../../include/Command.hpp"

inviteCMD::inviteCMD(Server& server): Command(server) {}

inviteCMD::~inviteCMD() {}

void    inviteCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string user = args.front();
    args.pop();
    std::string channel = args.front();
    args.pop();

    Client* user_ptr = this->_server.getClientByName(user);
    Channel* channel_ptr = this->_server.getChannel(channel);

    if (!channel_ptr)
    {
        return ;
    }
    if (!user_ptr)
    {
        return ;
    }
    if (channel_ptr->getInviteOnly() && !channel_ptr->isOperator(client))
    {
        return ;
    }
    
    channel_ptr->addInvited(user_ptr);
    user_ptr->queuePacket(RPL_INVITE(client->getNickname(), user, channel));
}