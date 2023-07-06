#include "../../include/Client.hpp"

void		Client::getArguments(std::string& packet)
{
    std::stringstream ss(packet);
    std::string arg;

    while (ss >> arg)
    {
        this->_args.push(arg);
    }
}

std::string Client::removeArgument()
{
    if (!this->_args.size())
    {
        throw std::runtime_error("Empty Queue!");
    }
    
    std::string arg = this->_args.front();
    this->_args.pop();

    return arg;
}

std::string Client::getRemainingArguments()
{
    std::string message_part = this->removeArgument();

    while (this->_args.size())
    {
        message_part += " " + this->removeArgument();
    }

    return message_part;
}

size_t  Client::queueSize() const { return this->_args.size(); }