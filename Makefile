# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 19:31:22 by mchliyah          #+#    #+#              #
#    Updated: 2022/06/15 00:10:32 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f
#########################
# ! files of the minishell
FILES =		 \
		main.c\
		lexer/lexer.c\
		lexer/lexer_utils.c\
		lexer/init_fun.c\
		lexer/ft_split_quote.c\

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
	@$(CC) -g $(CFLAGS) $(OBJECTS) $(ARLIB)  -lreadline -o $(NAME)
	@$(CLEANLIBFT)
	@echo "\033[1;33m ███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██ "
	@echo "\033[1;33m ████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██ "
	@echo "\033[1;33m ██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██ "
	@echo "\033[1;33m ██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██ "
	@echo "\033[1;33m ██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ "
	@echo "$(C_L_BLUE) 1.0"
	@echo " "
	@echo "\033[1;35m▐▌ DONE by @abdelhak4  & @mchliyah ▐▌"

clean : 
	@$(CLEANLIBFT)
	@$(RM) $(OBJECTS)
	@echo "$(C_RED)[MINISHELL OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(FCLEANLIBFT)
	@$(RM) $(NAME)
	@echo "$(C_RED)[MINISHELL OBJECTS && EXECUTABLES DELETED!]$(C_RES)"

re : fclean all
