NAME	= ircserv

OBJS	= $(subst src, objs, $(SRC:.cpp=.o))

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
HEADERS	= -I include
RM		= rm -rf
MKDIR	= mkdir -p

SRC		= $(addprefix src/, $(addsuffix .cpp, \
			main \
			$(addprefix Server/, \
			Server \
			ServerHandlers) \
			$(addprefix User/, \
			User) \
			$(addprefix Client/, \
			Client)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(HEADERS) -o $(NAME)

objs/%.o: src/%.cpp
	@$(MKDIR) objs
	@$(MKDIR) objs/Server
	@$(MKDIR) objs/User
	@$(MKDIR) objs/Client
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