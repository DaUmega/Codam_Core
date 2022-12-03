SRCS	= push_swap.c ft_lists.c operation.c algoa.c algob.c \
	smallsort.c nospace.c fivesort.c nospace2.c

OBJS	= $(SRCS:.c=.o)

NAME	= push_swap

LIBFT	= libft/libft.a

CFLAGS	= -Wall -Werror -Wextra

HEADERS = push_swap.h

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADERS)
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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