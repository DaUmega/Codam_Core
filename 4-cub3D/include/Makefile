# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pniezen <pniezen@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/25 09:32:45 by pniezen       #+#    #+#                  #
#    Updated: 2023/02/06 14:37:40 by pniezen       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS = ./include/cubed.h ./include/settings.h ./include/color.h
SRC_F = main.c key_hook.c utils.c parse_map.c free_ft.c list_utils.c inputparse.c\
		init_game.c color.c minimap.c minimap_utils.c raymath.c\
		playermath.c draw.c walls.c

SRC_D = ./src/
OBJ_D = ./obj/
INC_D = ./include/ ./lib/MLX42/include/ ./lib/libft/


MLX_D = ./lib/MLX42/
LIBFT_D = ./lib/libft/

MLX_A = $(MLX_D)libmlx42.a
LIBFT_A = $(LIBFT_D)libft.a

OBJ = $(addprefix $(OBJ_D), $(SRC_F:.c=.o))
INC = $(addprefix -I, $(INC_D))

FRAMEWORK = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit 
LIB = $(FRAMEWORK) $(MLX_A) $(LIBFT_A)

CFLAGS += $(INC)


all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling main executable"
	@make -C $(MLX_D)
	@make -C $(LIBFT_D)
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(HEADERS)
	@mkdir -p $(OBJ_D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -o $@ -c $<

cleanlib:
	@make -C $(MLX_D) clean
	@make -C $(LIBFT_D) clean

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_D)
	@echo "Cleaning"

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_D) fclean
	@make -C $(LIBFT_D) fclean

re: fclean all

.PHONY: clean, fclean, re, all

