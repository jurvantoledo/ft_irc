#include "../../../include/Command.hpp"

modeCMD::modeCMD(Server& server): Command(server) {}

modeCMD::~modeCMD() {}

void    modeCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string channel = args.front();
    args.pop();
    std::string modes;
    char        mode;

    std::string::iterator   it;
    bool    add = true;

    Channel*    channel_ptr = this->_server.getChannel(channel);

    if (!channel_ptr)
    {
        return ;
    }
    
    if (args.size() < 2)
    {
        return ;
    }
    if (!channel_ptr->isOperator(client))
    {
        return ;
    }
    
    modes = args.front();
    args.pop();

    for (std::string::const_iterator it = modes.begin(); it != modes.end(); it++)
    {
        mode = (*it);
        if (mode == '+')
            add = true;
        else if (mode == '-')
            add = false;
    
        switch (mode)
        {
        case 'i':
            if (add)
                channel_ptr->setInviteOnly(true);
            else
                channel_ptr->setInviteOnly(false);
            break;
        
        case 't':
            if (add)
                channel_ptr->setTopicOps(true);
            else
                channel_ptr->setTopicOps(false);
            break ;
        case 'k':
            if (add)
            {
                channel_ptr->setPassword(args.front());
                args.pop();
            }
            else
                channel_ptr->setPassword("");
            break ;
        case 'o':
        {
            std::string nick = args.front();
            args.pop();
            Client* user = this->_server.getClientByName(nick);

            if (!user)
            {
                break ;
            }
            if (!channel_ptr->isMember(user))
            {
                break ;
            }
            if (add)
                channel_ptr->addOperator(user);
            else
                channel_ptr->removeOperator(user);
            break ;
        }
        case 'l':
            if (add)
            {
                channel_ptr->setMaxUsers(atoi(args.front().c_str()));
                args.pop();
            }
            else
                channel_ptr->setMaxUsers(0);
            break ;
        default:
            break;
        }
    }
    channel_ptr->sendMessage(RPL_MODE(client->getNickname(), channel, channel_ptr->getModes()), client);
}