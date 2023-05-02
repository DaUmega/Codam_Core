SRCS	= main.cpp Bureaucrat.cpp Form.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= out

CFLAGS	= -Wall -Werror -Wextra -std=c++98

HEADERS = Bureaucrat.hpp Form.hpp

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