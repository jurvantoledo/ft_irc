#ifndef USER_H
#define USER_H
#include <iostream>

class User
{
	private:
		std::string username;
		std::string	full_name;
	public:
		User(/* args */);
		~User();
};

#endif