#include "../../include/Arguments.hpp"

Arguments::Arguments(std::string& packet)
{
    std::stringstream ss(packet);
    std::string arg;

    while (ss >> arg)
    {
        this->_queue.push(arg);
    }
}

Arguments::~Arguments() {}


std::string Arguments::removeArgument()
{
    if (!this->_queue.size())
    {
        throw std::runtime_error("Empty Queue!");
    }
    
    std::string arg = this->_queue.front();
    this->_queue.pop();

    return arg;
}

std::string Arguments::getRemainingArguments()
{
    std::string message_part = this->removeArgument();

    while (this->_queue.size())
    {
        message_part += " " + this->removeArgument();
    }

    return message_part;
}

size_t  Arguments::queueSize() const { return this->_queue.size(); }
