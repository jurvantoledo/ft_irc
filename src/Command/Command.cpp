#include "../../include/Command.hpp"

Command::Command(Server& server): _server(server), _authenticated(false) {}

Command::~Command() {}

bool	Command::getAuthenticated() const	{ return _authenticated; }
void	Command::setAuthenticated() 		{ _authenticated = true; }