#include "../../include/Command.hpp"
#include "../../include/CommandHandler.hpp"

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
    std::cout << "received packet: " << packet << std::endl;
    std::queue<std::string> args;
    Command*		command = NULL;
    char delim = ' ';
    size_t start = 0;
    size_t end = packet.find_first_of(delim);

    while (end != std::string::npos && start < 2)
    {
        std::string part = packet.substr(start, end - start);
        args.push(part);

        start = end + 1;
        end = packet.find_first_of(delim, start);
    }
    std::string last_part = packet.substr(start);
    args.push(last_part);

    if (!args.empty()) {
        command = this->getCommand(args.front());
        args.pop();
    }

    try
    {
        command->ExecCommand(client, args);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}