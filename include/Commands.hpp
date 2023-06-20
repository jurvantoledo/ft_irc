#ifndef COMMANDS_H
#define COMMANDS_H

class Commands
{
    typedef enum {
        NICK,
        USER,
        QUIT,
        JOIN,
        PART,
        LIST,
        PRIVMSG,
        WHO
    };

    private:
        
    public:
        Commands(/* args */);
        ~Commands();
};

#endif