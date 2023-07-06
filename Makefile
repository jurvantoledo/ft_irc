NAME	= ircserv

OBJS	= $(subst src, objs, $(SRC:.cpp=.o))

CC		= c++
CFLAGS	= -std=c++98
HEADERS	= -I include
RM		= rm -rf
MKDIR	= mkdir -p

SRC		= $(addprefix src/, $(addsuffix .cpp, \
			main \
			$(addprefix Server/, \
			Server \
			ServerHandlers \
			Networking \
			Poll \
			Client \
			Channel) \
			$(addprefix Client/, \
			Client \
			Receive \
			Send \
			User \
			Arguments) \
			$(addprefix Channel/, \
			Channel \
			Send \
			Members \
			Operators \
			Invited) \
			$(addprefix Command/, \
			Command \
			CommandHandler \
			$(addprefix Commands/, \
			Nick \
			User \
			Invite \
			Join \
			Kick \
			Mode \
			Pass \
			PrivMsg \
			Topic))))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(HEADERS) -o $(NAME)

objs/%.o: src/%.cpp
	@$(MKDIR) objs
	@$(MKDIR) objs/Server
	@$(MKDIR) objs/Client
	@$(MKDIR) objs/Channel
	@$(MKDIR) objs/Command
	@$(MKDIR) objs/Command/Commands
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@echo "Removing .o files"
	@$(RM) objs/

fclean:
	@echo "Cleaning up the workspace"
	$(RM) objs/
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re