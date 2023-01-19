SRCS	= main.cpp Weapon.cpp HumanA.cpp HumanB.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= violence

CFLAGS	= -Wall -Werror -Wextra -std=c++98 -pedantic

HEADERS = Weapon.hpp HumanA.hpp HumanB.hpp

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