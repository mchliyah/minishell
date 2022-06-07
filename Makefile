
NAME = minishell
SRCS = minishell.c\
	ft_itoa.c lexer.c


CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(SRCS)
	cc $(SRCS) -o $(NAME)
clean :
	rm -f $(NAME)
fclean : clean
re : fclean all
.PHONY: clean all clean re fclean