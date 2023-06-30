#include "Server.hpp"

Channel*    Server::addChannel(std::string channel, std::string password)
{
    Channel*    new_channel;

    new_channel = new Channel(channel, password);
    this->_channels[channel] = new_channel;

    return new_channel;
}

Channel*    Server::getChannel(std::string channel)
{
    std::map<std::string, Channel*>::iterator it;

    it = this->_channels.begin();
    while (it != this->_channels.end())
    {
        // If the channel name is found in the map return the channel
        if (it->first == channel)
        {
            return it->second;
        }
        it++;
    }
    return NULL;
}

void    Server::removeChannel(std::string channel)
{
    std::map<std::string, Channel*>::iterator it;

    it = this->_channels.find(channel);
    if (it == this->_channels.end())
        throw std::runtime_error("removeChannel() failed, client did not exsist");
    
    delete it->second;
    this->_channels.erase(it);
}