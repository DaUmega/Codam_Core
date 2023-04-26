SRCS	= main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= game

CFLAGS	= -Wall -Werror -Wextra -std=c++98 -pedantic

HEADERS = ClapTrap.hpp ScavTrap.hpp FragTrap.hpp

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