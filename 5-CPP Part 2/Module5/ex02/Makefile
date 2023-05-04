SRCS	= main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp\
		RobotomyRequestForm.cpp PresidentialPardonForm.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	= out

CFLAGS	= -Wall -Werror -Wextra -std=c++98

HEADERS = Bureaucrat.hpp AForm.hpp ShrubberyCreationForm.hpp\
		RobotomyRequestForm.hpp PresidentialPardonForm.hpp

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