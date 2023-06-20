#ifndef USER_H
#define USER_H
#include <iostream>

class User
{
	private:
		std::string _username;
		std::string	_fullName;
		std::string	_password;
		std::string _message;
		int			_userSockfd;

	public:
		User(/* args */);
		~User();

		// Getters
		std::string	getUsername() const;
		std::string	getPassword() const;
		std::string	getFullName() const;
		std::string	getMessage() const;
		int			getUserSocket() const;

		// Setters
		void	setUsername(std::string str);
		void	setFullName(std::string str);
		void	setPassword(std::string pass);
		void	setMessage(std::string mess);
		void	setUserSocket(int sockfd);
};

#endif