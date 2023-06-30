#ifndef CLIENT_H

#define CLIENT_H
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

class Client
{
	private:
		std::string _nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_password;

	public:
		// Getters
		std::string	getNickname() const;
		std::string	getUsername() const;
		std::string	getRealName() const;
		std::string	getPassword() const;

		// Setters
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setRealName(std::string realname);
		void		setPassword(std::string password);

	private:
		int				_socket;
		std::string		_buffer;
		bool			_dataToSend;

	public:
		Client();
		Client(int client_fd);
		~Client();

		bool			handleMessage();
		std::string		receiveMessage();
		void			sendMessage(int socket);
		bool			hasDataToSend();
	
		// Getters
		int			getSocket();
		bool		getDataToSend();


		// Setters
		void		setSocket(int fd);
		void		setDataToSend();
		void		clearDataToSend();

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