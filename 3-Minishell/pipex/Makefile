SRCS	= main.c ft_lists.c

OBJS	= $(SRCS:.c=.o)

NAME	= pipex
LIBFT	= libft/libft.a

CFLAGS	= -Wall -Werror -Wextra

HEADERS = 

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADERS)
	@gcc $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus