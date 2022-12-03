SRCS	= main.c utils.c philo.c philo_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

HEADERS = philo.h

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