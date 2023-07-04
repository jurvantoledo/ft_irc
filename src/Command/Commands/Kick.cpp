#include "../../../include/Command.hpp"

kickCMD::kickCMD(Server& server): Command(server) {}

kickCMD::~kickCMD() {}

void    kickCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string user = args.front();
    args.pop();
    std::string channel = args.front();
    args.pop();

    Channel* channel_ptr = this->_server.getChannel(channel);
    Client* user_ptr = this->_server.getClientByName(user);

    if (!channel_ptr)
        return ;
    if (!user_ptr)
        return ;
    if (!channel_ptr->isOperator(client))
        return ;
    if (!channel_ptr->isMember(user_ptr))
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));
    
    channel_ptr->removeMember(user_ptr);
}