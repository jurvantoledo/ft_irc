#ifndef COMMAND_H
#define COMMAND_H

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Arguments.hpp"
#include <queue>

class Channel;
class Server;

class Command
{
    protected:
        Server& _server;

    public:
        explicit Command(Server& server);
        virtual ~Command();

        virtual void    ExecCommand(Client* client, std::queue<std::string> args) = 0;
};

class nickCMD: public Command
{
    public:
        nickCMD(Server& server);
        ~nickCMD();

        void    ExecCommand(Client* client, std::queue<std::string> args);    
};

class userCMD: public Command
{
    public:
        userCMD(Server& server);
        ~userCMD();
    
    void    ExecCommand(Client* client, std::queue<std::string> args);    
};


#endif