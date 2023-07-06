#include "../../../include/Command.hpp"

modeCMD::modeCMD(Server& server): Command(server) {}

modeCMD::~modeCMD() {}

void    modeCMD::ExecCommand(Client* client)
{
    std::string channel = client->removeArgument();
    std::string modes;
    char        mode;
    bool    add = true;

    Channel*    channel_ptr = this->_server.getChannel(channel);

    if (!channel_ptr)
        return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channel));
    if (!client->queueSize())
        return (void)client->queuePacket(RPL_MODE(client->getNickname(), channel, channel_ptr->getModes()));
    if (!channel_ptr->isOperator(client))
        return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel));
    
    modes = client->removeArgument();

    for (std::string::iterator it = modes.begin(); it != modes.end(); it++)
    {
        mode = *((it)++);
        // if (mode == '+')
        //     add = true;
        // else if (mode == '-')
        //     add = false;
    
        switch (mode)
        {
            case '+': add = true;	break;
		    case '-': add = false;	break;
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
                    channel_ptr->setPassword(client->removeArgument());
                }
                else
                    channel_ptr->setPassword("");
                break ;
            case 'o':
            {
                std::string nick = client->removeArgument();
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
                    channel_ptr->setMaxUsers(atoi(client->removeArgument().c_str()));
                else
                    channel_ptr->setMaxUsers(0);
                break ;
            default:
                
                break;
        }
    }
    channel_ptr->sendMessage(RPL_MODE(client->getNickname(), channel, channel_ptr->getModes()), client);
}