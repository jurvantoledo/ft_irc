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

// std::string    CommandHandler::getRemainingArguments(std::queue<std::string> args)
// {
//     std::string full;

//     while (args.size())
//     {
//         full += " " + args.front();
//     }
    
//     return full;
// }

void    CommandHandler::registerUser(Client* client, std::string command, Arguments& args) const
{
    
    if (command == "USER" || command == "PASS")
    {
        Command* cmd = this->getCommand(command);
        if (cmd)
        {
            cmd->ExecCommand(client, args);
        }
        else
         {
            throw MessageException(command.c_str());
        }
    }
    return (void)client->queuePacket(ERR_NOTREGISTERED(client->getNickname()));
}

void    CommandHandler::Call(Client* client, std::string packet) const
{
    Arguments args(packet);
    std::string command;

    try
    {
        command = args.removeArgument();

        if (!client->getAuthenticatedUser())
        {
            this->registerUser(client, command, args);
            return ;
        }
        
        Command* cmd = this->getCommand(command);
        if (cmd)
            cmd->ExecCommand(client, args);
        else
        {
            throw MessageException(command.c_str());
        }
    }
    catch (const std::exception& e)
    {
        client->queuePacket(ERR_UNKNOWNCOMMAND(client->getNickname(), e.what()));
    }
}
