#include "../../include/Command.hpp"
#include "../../include/CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server): _server(server)
{
    this->_commands["NICK"] = new nickCMD(this->_server);
}

CommandHandler::~CommandHandler() {}


void    CommandHandler::Call(Client* client, std::string packet) const
{
    std::cout << "received packet: " << packet << std::endl;
    std::queue<std::string> args;
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


    while (!args.empty()) {
        std::string part = args.front();
        args.pop();

        // Process the part as required
        std::cout << "Part: " << part << std::endl;
    }
}