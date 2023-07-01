#include "../../../include/Command.hpp"

nickCMD::nickCMD(Server& server) : Command(server) {}

nickCMD::~nickCMD() {}

void    nickCMD::ExecCommand(Client* client, std::queue<std::string> args)
{
    std::cout << "set the nickname bruh: " << std::endl;
    return ;
}