#ifndef COMMAND_H
#define COMMAND_H

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Arguments.hpp"
#include "Replies.hpp"
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

        virtual void    ExecCommand(Client* client,  Arguments& args) = 0;
};

class nickCMD: public Command
{
    public:
        nickCMD(Server& server);
        ~nickCMD();

        void    ExecCommand(Client* client, Arguments& args);    
};

class userCMD: public Command
{
    public:
        userCMD(Server& server);
        ~userCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class passCMD: public Command
{
    public:
        passCMD(Server& server);
        ~passCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class inviteCMD: public Command
{
    public:
        inviteCMD(Server& server);
        ~inviteCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class joinCMD: public Command
{
    public:
        joinCMD(Server& server);
        ~joinCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class kickCMD: public Command
{
    public:
        kickCMD(Server& server);
        ~kickCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class privMsgCMD: public Command
{
    public:
        privMsgCMD(Server& server);
        ~privMsgCMD();
    
    void	toChannel(Client* client, std::string& target, Arguments& args);
    void	toClient(Client* client, std::string& target, Arguments& args);
    void    ExecCommand(Client* client, Arguments& args);    
};

class topicCMD: public Command
{
    public:
        topicCMD(Server& server);
        ~topicCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

class modeCMD: public Command
{
    public:
        modeCMD(Server& server);
        ~modeCMD();
    
    void    ExecCommand(Client* client, Arguments& args);    
};

#endif