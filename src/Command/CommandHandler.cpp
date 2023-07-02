#include "../../include/Command.hpp"
#include "../../include/CommandHandler.hpp"
#include <sstream>

CommandHandler::CommandHandler(Server& server): _server(server)
{
    this->_commands["NICK"] = new nickCMD(this->_server);
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
        std::istringstream iss(packet);
        std::string command;
        iss >> command;

        Command* cmd = this->getCommand(command);
        if (cmd)
        {
            std::queue<std::string> args;
            std::string arg;
            while (iss >> arg)
            {
                args.push(arg);
            }

            client->setIsCommand();
            cmd->ExecCommand(client, args);
        }
        else
        {
            // Handle unsupported command or message
            client->hasDataToSend();
            client->clearCommand();
            client->setDataToSend();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}