SRCS	= get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= gnl.a

CFLAGS	= -Wall -Werror -Wextra

HEADERS = get_next_line.h

CC		= @gcc
RM		= @rm -f

$(NAME): $(OBJS)
	@ar rcs $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re