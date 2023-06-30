#ifndef COMMAND_H
#define COMMAND_H

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Arguments.hpp"

class Channel;
class Server;

class Command
{
    protected:
        Server& _server;

    public:
        explicit Command(Server& server);
        virtual ~Command();

        virtual void    ExecCommand(Client* client, Arguments* args) = 0;
};

class nickCMD: public Command
{
    public:
        nickCMD(Server& server);
        ~nickCMD();

        void    ExecCommand(Client* client, Arguments* args);    
};

class userCMD: public Command
{
    public:
        userCMD(Server& server);
        ~userCMD();
    
    void    ExecCommand(Client* client, Arguments* args);    
};


#endif