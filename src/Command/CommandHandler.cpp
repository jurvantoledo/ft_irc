#include "../../include/Command.hpp"
#include "../../include/CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server): _server(server)
{
    this->_commands["NICK"] = new nickCMD(this->_server);
    this->_commands["USER"] = new userCMD(this->_server);
    this->_commands["PASS"] = new passCMD(this->_server);
    this->_commands["PRIVMSG"] = new privMsgCMD(this->_server);
    this->_commands["JOIN"] = new joinCMD(this->_server);
    this->_commands["TOPIC"] = new topicCMD(this->_server);
    this->_commands["KICK"] = new kickCMD(this->_server);
    this->_commands["INVITE"] = new inviteCMD(this->_server);
    this->_commands["MODE"] = new modeCMD(this->_server);
}

CommandHandler::~CommandHandler() 
{
    std::map<std::string, Command*>::iterator it;

    for (it = this->_commands.begin(); it != this->_commands.end(); it++)
        delete it->second;
}


Command*    CommandHandler::getCommand(std::string& command) const
{
    std::map<std::string, Command*>::const_iterator it = this->_commands.find(command);
    if (it != this->_commands.end())
    {
        return it->second;
    }
    return NULL;
}

void    CommandHandler::Call(Client* client, std::string packet) const
{
    client->getArguments(packet);
    std::string command;

    try
    {
        Command* cmd;

        command = client->removeArgument();
        cmd = this->getCommand(command);
        
        if(!client->getAuthenticatedUser() && (command == "USER" || command == "PASS" || command == "NICK"))
        {
            if (client->getNickname().empty() || client->getPassword().empty() \
                || client->getUsername().empty() || client->getRealName().empty())
                try { 
                    cmd->ExecCommand(client);
                    if (client->queueSize())
		                client->eraseArgument(); 
                }
                catch(const std::out_of_range& e)	{ return ; }
        }
        else
        {
            if (!client->getNickname().empty() && !client->getPassword().empty() && \
                !client->getUsername().empty() && !client->getRealName().empty())
                cmd->setAuthenticated();
            else
            {
                if (client->queueSize())
		            client->eraseArgument(); 
                return (void)client->queuePacket(ERR_NOTREGISTERED(client->getNickname()));
            }
            
        }
        if (cmd->getAuthenticated() == true)
        {
            try { 
                cmd->ExecCommand(client); 
                if (client->queueSize())
		            client->eraseArgument(); 
            }
            catch(const std::out_of_range& e)	{ return ; }
        }
    }
    catch (const std::exception& e)
    {
        client->eraseArgument();
        client->queuePacket(ERR_UNKNOWNCOMMAND(client->getNickname(), e.what()));
    }
}
