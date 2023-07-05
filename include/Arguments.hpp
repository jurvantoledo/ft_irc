#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

class Arguments
{
    private:
        std::queue<std::string>	_queue;

    public:
        Arguments(std::string& packet);
        ~Arguments();

        std::string removeArgument();
        std::string getRemainingArguments();
        size_t      queueSize() const;
};

#endif