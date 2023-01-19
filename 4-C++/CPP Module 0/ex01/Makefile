SRCS	= main.cpp Contacts.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= phonebook

CFLAGS	= -Wall -Werror -Wextra -std=c++98 -pedantic

HEADERS = Contacts.hpp

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