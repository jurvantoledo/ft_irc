#ifndef COMMAND_H
#define COMMAND_H

class Command
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
        Command(/* args */);
        ~Command();
};

#endif