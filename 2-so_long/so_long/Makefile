SRCS	= main.c free_ft.c parsemap.c pathfinder.c path_utils.c \
	graphics.c graphics_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= so_long

LIBFT	= libft/libft.a
MLX		= MLX42/libmlx42.a

CFLAGS	= -Wall -Werror -Wextra

HEADERS = so_long.h

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX) $(HEADERS)
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C MLX42

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C MLX42 

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C MLX42

re: fclean all

.PHONY: all clean fclean re bonus