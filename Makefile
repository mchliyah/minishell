# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 19:31:22 by mchliyah          #+#    #+#              #
#    Updated: 2022/08/20 18:34:23 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Wall -Werror -Wextra

#READFLAG = -lreadline -L /Users/mchliyah/Desktop/.brew/opt/readline/lib -I /Users/mchliyah/Desktop/.brew/opt/readline/include
READFLAG = -lreadline -L /goinfre/ael-mous/.brew/opt/readline/lib -I /goinfre/ael-mous/.brew/opt/readline/include
RM = rm -f
#########################
# ! files of the minishell
FILES =	main.c\
		init.c\
		init_utils.c\
		lexer/free_lexer.c\
		lexer/lexer.c\
		lexer/check_rederections.c\
		lexer/lexer_utils.c\
		lexer/init_fun.c\
		lexer/lexer_quotes_checker.c\
		lexer/args_getter.c\
		lexer/arg_lst_fun.c\
		lexer/expending.c\
		lexer/expending_utils.c\
		lexer/arg_scanner.c\
		lexer/lexer_helper.c\
		lexer/lexer_utils_holder.c\
		lexer/expending_cmd.c\
		lexer/expending_file_holeder.c\
		lexer/expending_here_doc.c\
		lexer/cmd_getter.c\
		lexer/cmd_getter_file_holder.c\
		parser/parser.c\
		parser/pars_utils.c\
		error.c\
		free.c\
		parser/print.c\
		parser/parser_utils.c\
		exec.c\
		builtins/builtins.c\
		builtins/std_exec.c\
		iterator.c\
		builtins/echo.c\
		builtins/env.c\
		builtins/cd.c\
		builtins/cd_utils.c\
		builtins/pwd.c\
		builtins/unset.c\
		builtins/array_args.c\
		builtins/export.c\
		builtins/export_utils.c\
		builtins/exit.c\
		here_doc/here_doc.c\

#!########################

OBJECTS =  $(FILES:.c=.o)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $^ -o $@

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
	@$(CC)  $(READFLAG) $(OBJECTS) $(ARLIB) -o  $(NAME) #-fsanitize=address -g3
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
