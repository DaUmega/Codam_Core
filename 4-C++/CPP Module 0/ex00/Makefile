SRCS	= megaphone.cpp

OBJS	= $(SRCS:.c=.o)

NAME	= megaphone

CFLAGS	= -Wall -Werror -Wextra -std=c++98

HEADERS = 

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@g++ $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@g++ $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus