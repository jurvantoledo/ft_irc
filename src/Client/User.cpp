#include "../../include/Client.hpp"

// Getters
std::string     Client::getNickname() const { return (_nickname); }
std::string     Client::getUsername() const { return (_username); }
std::string     Client::getRealName() const { return (_realname); }
std::string     Client::getPassword() const { return (_password); }
bool            Client::getAuthenticatedUser() const { return (_already_exists); }

// Setters
void    Client::setNickname(std::string nickname) { _nickname = nickname; }
void    Client::setUsername(std::string username) { _username = username; }
void    Client::setRealName(std::string realname) { _realname = realname; }
void    Client::setPassword(std::string password) { _password = password; }
void    Client::setAuthenticatedUser() { _already_exists = true; }
