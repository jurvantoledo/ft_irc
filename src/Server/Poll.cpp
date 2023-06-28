#include "../../include/Server.hpp"

void	Server::setPollFlag(pollfd &pfd, short events)
{

	pfd.events |= events;
}

void	Server::removePollFlag(pollfd &pfd, short event)
{
	pfd.events &= ~event;
}