SRCS	= ft_atoi.c ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_split.c ft_isalpha.c \
	ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
	ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memcpy.c \
	ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
	ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c  \
	ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c

OBJS	= $(SRCS:.c=.o)

NAME	= libft.a
PRINTF	= ft_printf/ft_printf.o ft_printf/ft_support.o
GNL		= get_next_line/get_next_line.o get_next_line/get_next_line_utils.o

CFLAGS	= -Wall -Werror -Wextra

HEADERS = libft.h

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(PRINTF) $(GNL)
	ar rcs $(NAME) $(OBJS) $(PRINTF) $(GNL)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(PRINTF):
	make -C ft_printf

$(GNL):
	make -C get_next_line

clean:
	$(RM) $(OBJS)
	make clean -C ft_printf
	make clean -C get_next_line

fclean: clean
	$(RM) $(NAME)
	make fclean -C ft_printf
	make fclean -C get_next_line

re: fclean all

.PHONY: all clean fclean re bonus