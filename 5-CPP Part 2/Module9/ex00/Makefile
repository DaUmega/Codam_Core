SRCS	= main.cpp BitcoinExchange.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= btc

CFLAGS	= -Wall -Werror -Wextra -std=c++98

HEADERS =  BitcoinExchange.hpp

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@c++ $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	@c++ $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus