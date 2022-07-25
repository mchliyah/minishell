# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 19:31:22 by mchliyah          #+#    #+#              #
#    Updated: 2022/07/25 03:01:05 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc

CFLAGS = #-Wall -Werror -Wextra 
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

RM = rm -f
#########################
# ! files of the minishell
FILES =	main.c\
		lexer/lexer.c\
		lexer/lexer_utils.c\
		lexer/init_fun.c\
		lexer/ft_split_quote.c\
		lexer/lexer_quotes_checker.c\
		lexer/args_getter.c\
		lexer/arg_lst_fun.c\
		lexer/expending.c\
		lexer/expending_utils.c\
		lexer/arg_scanner.c\
		lexer/lexer_helper.c\
		lexer/expending_cmd.c\
		lexer/ft_split_arg_utils.c\
		parser/parser.c\
		parser/pars_utils.c\
		parser/error.c\
		parser/free.c\
		parser/print.c\
		exec.c\
		builtins/echo.c\
		builtins/env.c\
		builtins/cd.c\
		builtins/pwd.c\
		builtins/exit.c\
		builtins/unset.c

#!########################

OBJECTS =  $(FILES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

LIBFT = ./libft
ARLIB = $(LIBFT)/libft.a
ALLIBFT = make -C $(LIBFT)
CLEANLIBFT = make clean -C $(LIBFT)
FCLEANLIBFT = rm -f $(ARLIB)
RELIBFT = make re -C $(LIBFT)

#######################
#! C O L O R  V A R S  #
######################
C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m
#######################

.PHONY: clean all clean re fclean

all : $(NAME)

$(NAME) :  $(OBJECTS)
	@$(ALLIBFT)
	@$(CC) $(CFLAGS) -g $(OBJECTS) $(ARLIB)  -lreadline -o $(NAME) -fsanitize=address -g3
	@$(CLEANLIBFT)
	@echo "\033[1;33m ███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██ "
	@echo "\033[1;33m ████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██ "
	@echo "\033[1;33m ██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██ "
	@echo "\033[1;33m ██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██ "
	@echo "\033[1;33m ██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ "
	@echo "$(C_L_BLUE) 1.0"
	@echo " "
	@echo "\033[1;35m▐▌ DONE by @abdelhak4  & @mchliyah ▐▌$(C_RES)"

clean : 
	@$(CLEANLIBFT)
	@$(RM) $(OBJECTS)
	@echo "$(C_RED)[MINISHELL OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(FCLEANLIBFT)
	@$(RM) $(NAME)
	@echo "$(C_RED)[MINISHELL OBJECTS && EXECUTABLES DELETED!]$(C_RES)"

re : fclean all
