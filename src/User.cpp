#include "../include/User.hpp"

User::User()
{
}

User::~User()
{
}

std::string    User::getUsername() const
{
    return (_username);
}

std::string     User::getPassword() const
{
    return (_password);
}


std::string     User::getFullName() const
{
    return (_fullName);
}

std::string     User::getMessage() const
{
    return (_message);
}

int             User::getUserSocket() const
{
    return (_userSockfd);
}

void    User::setUsername(std::string str)
{
    _username = str;
}

void    User::setPassword(std::string pass)
{
    _password = pass;
}

void    User::setFullName(std::string str)
{
    _fullName = str;
}

void    User::setMessage(std::string mess)
{
    _message = mess;
}

void    User::setUserSocket(int sockfd)
{
    _userSockfd = sockfd;
}