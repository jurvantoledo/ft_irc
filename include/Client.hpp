#ifndef CLIENT_H

#define CLIENT_H
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

class Client
{
	private:
		int				_socket;
		std::string		_buffer;

	public:
		Client();
		Client(int client_fd);
		~Client();

		void		handleMessage(int socket, std::string packet);
		std::string receiveMessage();

		// Getters
		int			getSocket();
		// Setters
		void		setSocket(int fd);

};

#endif