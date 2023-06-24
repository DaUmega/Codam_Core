NAME	= webserv

CC	= c++

CFLAGS	= -Wall -Werror -Wextra -std=c++98

SRC_DIR	=	src

SRCS	:=	$(shell find src -type f | sed -e 's/src\///')

OBJS_DIR	=	objs

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

HEAD_PATHS	=	-I./inc

HEADERS	=	$(shell find inc -type f)

RM	= rm -f

_UPLOADS = www/_uploads

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$@ ready"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEAD_PATHS)

$(OBJS_DIR):
	@mkdir -p $@

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf $(_UPLOADS)

re: fclean all

.PHONY: all clean fclean re