#ifndef COMMANDS_H
#define COMMANDS_H

class Commands
{
    typedef enum userCmds {
        NICK,
        USER,
        PASS
    };

    typedef enum serverCmds {
        PING,
        OPEN,
        KILL
    };

    typedef enum channelCmds {
        JOIN,
        PART,
        INVITE,
        KICK,
        PRIVMSG,
        NOTICE
    };

    private:
        
    public:
        Commands(/* args */);
        ~Commands();
};

#endif