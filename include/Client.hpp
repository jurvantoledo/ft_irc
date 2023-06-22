#ifndef CLIENT_H

#define CLIENT_H
#include <iostream>

class Client
{
	private:
		int				_client_fd;

	public:
		Client(int client_fd);
		~Client();
};

#endif