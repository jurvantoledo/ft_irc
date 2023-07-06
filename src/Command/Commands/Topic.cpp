#include "../../../include/Command.hpp"

topicCMD::topicCMD(Server& server): Command(server) {}

topicCMD::~topicCMD() {}

void    topicCMD::ExecCommand(Client* client)
{
    std::string channelName = client->removeArgument();
    std::string topic;

    Channel* channel = this->_server.getChannel(channelName);

    if (!channel)
        return (void)client->queuePacket(ERR_WRONGCHANNAME(client->getNickname(), channelName));

    if (client->queueSize())
    {
        topic = client->getRemainingArguments();

        if (!channel->isOperator(client) && channel->getTopicOps())
            return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
        
        channel->setTopic(topic);
        channel->sendMessage(RPL_TOPIC(client->getNickname(), channelName, topic), client);
    }

    return (void)client->queuePacket(RPL_TOPIC(client->getNickname(), channelName, channel->getTopic()));
}