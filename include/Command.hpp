#ifndef COMMAND_H
#define COMMAND_H

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Arguments.hpp"

class Command
{
    protected:
    Server& _server;

    public:
        Command(Server& server);
        virtual ~Command();

        virtual void    ExecCommand(Client* client, Arguments* args) = 0;
};

#endif