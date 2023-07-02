#include "../../../include/Command.hpp"

nickCMD::nickCMD(Server& server) : Command(server) {}

nickCMD::~nickCMD() {}

void    nickCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string nickname = args.front();

    if (client->getNickname() == nickname)
    {
        std::cout << "nickname: " << nickname << " Already in use!" << std::endl;
        client->clearDataToSend(); // Clear any pending data to send
        client->setDataToSend(); // Set the data to send flag
        client->clearCommand();
        return ;
    }
    
    client->setNickname(nickname);

    std::cout << "Nickname is set for client #" << client->getSocket() << " nickname is -> " << nickname << std::endl;
    client->clearDataToSend();
}