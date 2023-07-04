#include "../../../include/Command.hpp"

topicCMD::topicCMD(Server& server): Command(server) {}

topicCMD::~topicCMD() {}

void    topicCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string channel = args.front();
    args.pop();
    std::string topic;

    Channel* channel_ptr = this->_server.getChannel(channel);

    if (!channel_ptr)
    {
        return ;
    }
    if (args.size() < 2)
    {
        return ;
    }
    
    topic = args.front();
    if (!channel_ptr->isOperator(client) && channel_ptr->getTopicOps())
        return ;

    channel_ptr->setTopic(topic);
    channel_ptr->sendMessage(RPL_TOPIC(client->getNickname(), channel, topic), client);
}