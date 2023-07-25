SRCS	= main.c parser.c gridcheck.c algorithm.c

OBJS	= $(SRCS:.c=.o)

NAME	= rush01

CFLAGS	= -Wall -Werror -Wextra

HEADERS = sky.h

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus