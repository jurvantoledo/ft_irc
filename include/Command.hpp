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
        bool    _authenticated;

    public:
        explicit Command(Server& server);
        virtual ~Command();

        virtual void    ExecCommand(Client* client) = 0;

        bool    getAuthenticated() const;
        void    setAuthenticated();

};

class nickCMD: public Command
{
    public:
        nickCMD(Server& server);
        ~nickCMD();

        void    ExecCommand(Client* client);    
};

class userCMD: public Command
{
    public:
        userCMD(Server& server);
        ~userCMD();
    
    void    ExecCommand(Client* client);    
};

class passCMD: public Command
{
    public:
        passCMD(Server& server);
        ~passCMD();
    
    void    ExecCommand(Client* client);    
};

class inviteCMD: public Command
{
    public:
        inviteCMD(Server& server);
        ~inviteCMD();
    
    void    ExecCommand(Client* client);    
};

class joinCMD: public Command
{
    public:
        joinCMD(Server& server);
        ~joinCMD();
    
    void    ExecCommand(Client* client);    
};

class kickCMD: public Command
{
    public:
        kickCMD(Server& server);
        ~kickCMD();
    
    void    ExecCommand(Client* client);    
};

class privMsgCMD: public Command
{
    public:
        privMsgCMD(Server& server);
        ~privMsgCMD();
    
    void	toChannel(Client* client, std::string& target);
    void	toClient(Client* client, std::string& target);
    void    ExecCommand(Client* client);    
};

class topicCMD: public Command
{
    public:
        topicCMD(Server& server);
        ~topicCMD();
    
    void    ExecCommand(Client* client);    
};

class modeCMD: public Command
{
    public:
        modeCMD(Server& server);
        ~modeCMD();
    
    void    ExecCommand(Client* client);    
};

#endif