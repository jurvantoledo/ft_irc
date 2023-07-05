#ifndef CLIENT_H

#define CLIENT_H
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <queue>

class Client
{
	private:
		std::string _nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_password;
		bool		_authenticated;

	public:
		// Getters
		std::string	getNickname() const;
		std::string	getUsername() const;
		std::string	getRealName() const;
		std::string	getPassword() const;
		bool		getAuthenticatedUser() const;

		// Setters
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setRealName(std::string realname);
		void		setPassword(std::string password);
		void		setAuthenticatedUser();

	private:
		int				_socket;
		std::string		_buffer;
		std::string		_packet;
		bool			_dataToSend;
		bool			_isCommand;
		std::queue<std::string>		_queue;

	public:
		Client();
		Client(int client_fd);
		~Client();

		bool			handleMessage();
		std::string		receiveMessage();
		void			sendMessage(Client* client);

		bool			hasDataToSend();
	
		int			getSocket();
		void		setSocket(int fd);

		// bool		getDataToSend();
		// void		setDataToSend();
		// void		clearDataToSend();

		// bool		getIsCommand();
		// void		setIsCommand();
		// void		clearCommand();


		// std::string		getPacket();
		// void			setPacket(std::string packet);

		size_t			getQueueSize();
		bool			processQueue();
		bool			sendPacket();
		void			queuePacket(std::string packet);

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