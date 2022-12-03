CLIENT	= client.c
SERVER	= server.c

OCLIENT	= $(CLIENT:.c=.o)
OSERVER	= $(SERVER:.c=.o)

NCLIENT	= client
NSERVER	= server

LIBFT	= libft/libft.a

CFLAGS	= -Wall -Werror -Wextra

HEADERS = libft.h

RM		= rm -f

all: $(NCLIENT) $(NSERVER)

$(NCLIENT): $(OCLIENT) $(LIBFT)
	gcc $(CFLAGS) $(CLIENT) $(LIBFT) -o $(NCLIENT)

$(NSERVER): $(OSERVER) $(LIBFT)
	gcc $(CFLAGS) $(SERVER) $(LIBFT) -o $(NSERVER)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OCLIENT) $(OSERVER)
	make clean -C libft

fclean: clean
	$(RM) $(NCLIENT) $(NSERVER)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus