SRCS	= main.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= brain

CFLAGS	= -Wall -Werror -Wextra -std=c++98 -pedantic

HEADERS = 

RM		= @rm -f

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@g++ $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	@g++ $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus