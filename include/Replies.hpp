#ifndef REPLIES_H
#define REPLIES_H

// RPL
#define RPL_WELCOME(origin)						"001 " + origin + " :Welcome " + origin
#define RPL_MODE(origin, channel, modes)		"324 " + origin + " " + channel + " " + modes
#define RPL_PRIVMSG(origin, target, message)	":" + origin + " PRIVMSG " + target + " :" + message
#define RPL_PART(origin, channel)				":" + origin + " PART :" + channel
#define RPL_LEAVE(origin, channel)				":" + origin + " LEAVES :" + channel
#define RPL_JOIN(origin, channel)				":" + origin + " JOIN :" + channel
#define RPL_TOPIC(origin, channel, topic)		":" + origin + " TOPIC " + channel + " :" + topic
#define RPL_INVITE(origin, invited, channel)	":" + origin + " INVITE " + invited + " :" + channel

// 4xx (error)
#define ERR_UNKNOWNERROR(command)				"400 " + std::string(command) + ":Unknown error"
#define ERR_WRONGCHANNAME(origin, target)		"401 " + origin + " " + target + " :No such origin/channel. Check if # is used for channel name"
#define ERR_NOSUCHNICK(origin, target)			"401 " + origin + " " + target + " :No such origin/channel"
#define ERR_CANNOTSENDTOCHAN(origin, channel)	"404 " + origin + " " + channel + " :You cannot sent messages to this channel"
#define ERR_UNKNOWNCOMMAND(origin, command)		"421 " + origin + " " + command + " :Unknown command"
#define ERR_NICKNAMEINUSE(origin)				"433 " + origin + " " + origin  + " :originname is already in use by another user"
#define ERR_NICKNAMENOTSET(origin)				"433 " + origin + " " + origin  + " :originname is empty"
#define ERR_NOTAMEMBER(origin, target, channel)	"441 " + origin + " " + target + " " + channel + " :They aren't on that channel"
#define ERR_NOTREGISTERED(origin)				"451 " + origin + " :You are not registered yet. Please set a Nickname, Username and password"
#define ERR_NEEDMOREPARAMS(origin, command)		"461 " + origin + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(origin)			"462 " + origin + " :You are already registered"
#define ERR_PASSWDMISMATCH(origin)				"464 " + origin + " :Incorrect password"
#define ERR_CHANNELISFULL(origin, channel)		"471 " + origin + " " + channel + " :Channel is full (+l)"
#define ERR_UNKNOWNMODE(origin, mode, channel)	"472 " + origin + " " + mode + " :is unknown mode char to me for " + channel
#define ERR_INVITEONLY(origin, channel)			"473 " + origin + " " + channel + " :Cannot join channel (+i)"
#define ERR_WRONGCHANPASS(origin, channel)		"475 " + origin + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED(origin, channel)	"482 " + origin + " " + channel + " :You are not a channel operator"


#endif