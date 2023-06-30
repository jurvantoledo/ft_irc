#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Server.hpp"
#include "Client.hpp"
#include "Command.hpp"

class CommandHandler
{
    private:
        Server& _server;
        std::map<std::string, Command*> _commands;
    private:
        Command*    getCommand(std::string& command) const;

    public:
        CommandHandler(Server& server);
        ~CommandHandler();

        void    addCommand(Client* client, std::string packet) const;
};


#endif