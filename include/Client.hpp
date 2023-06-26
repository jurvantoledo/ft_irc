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

		std::string		handleMessage();
		void			receiveMessage(int socket);

		// Getters
		int			getSocket();

		// Setters
		void		setSocket(int fd);

		// Exceptions
		class MessageException : public std::exception {
			private:
				const char		*_reason;
			public:
				MessageException(const char *reason): _reason(reason) {}
				const char *what() const throw() { return _reason; }
		};
};

#endif