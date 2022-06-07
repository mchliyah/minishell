# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 01:39:25 by ael-mous          #+#    #+#              #
#    Updated: 2021/11/20 18:53:30 by ael-mous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS = ft_bzero.c\
        ft_calloc.c\
        ft_isalpha.c\
        ft_isdigit.c\
        ft_isascii.c\
        ft_isalnum.c\
        ft_isprint.c\
        ft_itoa.c\
        ft_memcpy.c\
        ft_memmove.c\
        ft_memset.c\
        ft_memchr.c\
        ft_memcmp.c\
        ft_putstr_fd.c\
        ft_putendl_fd.c\
        ft_putchar_fd.c\
        ft_putnbr_fd.c\
        ft_strlcat.c\
        ft_strlcpy.c\
        ft_strlen.c\
        ft_strchr.c\
        ft_strdup.c\
        ft_strncmp.c\
        ft_strnstr.c\
        ft_strrchr.c\
        ft_strtrim.c\
        ft_substr.c\
        ft_atoi.c\
        ft_strjoin.c\
        ft_striteri.c\
        ft_strmapi.c\
        ft_toupper.c\
        ft_tolower.c\
        ft_split.c

BONUS = ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c

FLAGS = gcc -Wall -Werror -Wextra

NAME = libft.a

OBJ = $(SRCS:.c=.o)

OBJS = $(BONUS:.c=.o)

all : $(NAME)

bonus : $(OBJS)

$(NAME) : $(OBJ)

%.o : %.c
	$(FLAGS) -c $< -o $@
	ar rc libft.a $@
clean :
	rm -f $(OBJ) $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all