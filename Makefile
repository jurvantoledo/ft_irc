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
			Poll) \
			$(addprefix User/, \
			User) \
			$(addprefix Client/, \
			Client \
			Receive \
			Send) \
			$(addprefix Channel/, \
			Channel)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(HEADERS) -o $(NAME)

objs/%.o: src/%.cpp
	@$(MKDIR) objs
	@$(MKDIR) objs/Server
	@$(MKDIR) objs/User
	@$(MKDIR) objs/Client
	@$(MKDIR) objs/Channel
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