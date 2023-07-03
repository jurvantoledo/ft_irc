#include "../../include/Command.hpp"
#include "../../include/CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server): _server(server)
{
    this->_commands["NICK"] = new nickCMD(this->_server);
    this->_commands["USER"] = new userCMD(this->_server);
}

CommandHandler::~CommandHandler() {}


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
    try
    {
        std::stringstream ss(packet);
        std::string command;
        ss >> command;

        Command* cmd = this->getCommand(command);
        if (cmd)
        {
            std::queue<std::string> args;
            std::string arg;
            while (ss >> arg)
            {
                args.push(arg);
            }

            client->setIsCommand();
            cmd->ExecCommand(client, args);
            client->clearDataToSend();
            args.pop();
            return ;
        }
        else
        {
            // Handle unsupported command or message
            client->setPacket(packet);
            client->hasDataToSend();
            client->clearCommand();
            client->setDataToSend();
            return ;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}