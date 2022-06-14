
NAME = minishell
SRCS = minishell.c\
	 lexer.c libft/libft.a


CFLAGS = -Wall -Werror -Wextra -lreadline -fsanitize=address -g3
all : $(NAME)

$(NAME) : $(SRCS)
	cc -lreadline  $(SRCS) -o $(NAME)
clean :
	rm -f $(NAME)
fclean : clean
re : fclean all
.PHONY: clean all clean re fclean