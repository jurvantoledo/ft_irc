#include "../../../include/Command.hpp"

userCMD::userCMD(Server& server): Command(server) {}

userCMD::~userCMD() {}

void    userCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::string username = args.front();
    args.pop();
    std::string realname = args.front();
    args.pop();
    // std::string password = args.front();
    // args.pop();

    if (client->getAuthenticatedUser())
    {
        std::cout << "[Client]: " << "[" << client->getNickname() << "]" << " already exists!" << std::endl;
        client->clearDataToSend(); // Clear any pending data to send
        client->setDataToSend(); // Set the data to send flag
        return ;
    }
    
    std::cout << client->getPassword() << std::endl;
    if (!this->_server.checkPassword(client->getPassword()))
    {
        std::cout << "User: " << client->getUsername() << " with wrong password!" << std::endl;
        client->clearDataToSend(); // Clear any pending data to send
        client->setDataToSend(); // Set the data to send flag
        return ;
    }
    
    client->setUsername(username);
    client->setRealName(realname);

    if (client->getNickname().empty())
    {
        client->clearDataToSend(); // Clear any pending data to send
        client->setDataToSend(); // Set the data to send flag
        return ;
    }
    
    client->setAuthenticatedUser();
    std::cout << "User is set for client #" << client->getSocket() << " username is -> " << username << " | and realname is -> " << realname << std::endl;

    client->clearDataToSend(); // Clear any pending data to send
    client->setDataToSend(); // Set the data to send flag
}