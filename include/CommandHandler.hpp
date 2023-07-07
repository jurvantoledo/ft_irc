#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Server.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Replies.hpp"
#include <queue>
#include <sstream>

class Server;
class Command;

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

        void    Call(Client* client, std::string packet) const;

        // std::string getRemainingArguments(std::queue<std::string> args);

    	class MessageException : public std::exception {
			private:
				const char		*_reason;
			public:
				MessageException(const char *reason): _reason(reason) {}
				const char *what() const throw() { return _reason; }
		};

};


#endif