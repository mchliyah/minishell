/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/17 09:50:38 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/minishell.h"

t_lexer	*advance(t_lexer *lexer)
{
	if (lexer->i < lexer->str_len)
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
	return (lexer);
}

int	ft_is_symbol(char c)
{
	if (c == EPIPE || c == LESS || c == GREATER || c == SPACE || c == '\0')
		return (1);
	return (0);
}

int	check_quote(char cu, char c, int i)
{
	if (ft_strchr(SYMBOLS, cu) && (i == 0 || i%2==0))
		return (1);
	else if ((c == SINGLE_QUOTE || c == L_DOBLE_QUOTE)
			&& ft_strchr(SYMBOLS, cu) && i%2 == 0)
		return (1);
	return (0);
}

char	*check_for_args(t_lexer **this, int i) {
	char *ptr;
	char h;
	char *str;

	ptr = NULL;
	(void)i;
	if ((*this)->c == SPACE)
		*this = advance(*this);
	if (!ft_is_symbol((*this)->c))
		ptr = ft_strdup("");
	while ((*this)->c != '\0')
	{
		str = malloc(2 * sizeof(char));
		ft_bzero(str, 2);
		str[0] = (*this)->c;
		ptr = ft_strjoin(ptr, str);
		free(str);
		h = (*this)->c;
		*this = advance(*this);
	}
	return (ptr);
}

// count how options of the current cmd
/*int	c_arg(t_lexer *this)
{
	size_t	i;
	char	c;

	i = this->i;
	c = this->content[i];
	if (c == SPACE)
		c = this->content[i+1];
	while (c != '\0')
	{
		if (ft_strchr("\"\'",c))
		c = this->content[this->i++];
	}
}
char	**get_args(char **arg, t_lexer **lexer)
{
	 c_arg(*lexer);
}
void	check_for_nested_quote(t_lexer **this)
{
	int 	i;
	t_lexer *tmp;

	tmp = *this;
	i = 0;
	while (tmp->c != '0' && ft_strchr("\"\'",tmp->c))
	{
		if (i)
		tmp = advance(tmp);
		i++;
	}
}`*/

/*
  @todo	:
 */
t_token *get_char(t_lexer **lex)
{
	char	h;
	int 	i;
	char	*ptr;
	char	*str;
//	char **args = NULL;

	i = 0;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while ((*lex)->c != '\0' && ft_isprint((*lex)->c))
	{
//		check_for_nested_quote(lex);
//		if (ft_strchr("\"\'",(*lex)->c))
//		{
//			*lex = advance(*lex);
//			i++;
//		}
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
		ft_bzero(str, 2);
		str[0] = (*lex)->c;
		ptr = ft_strjoin(ptr, str);
		if (!ptr)
			return (NULL);
		free(str);
		str = NULL;
		h  = (*lex)->c;
		*lex = advance(*lex);
		if (check_quote((*lex)->c, h, i)) {
			break ;
		}
	}
//	get_args(args, lex);
	check_for_args(lex, i);
	return (init_token(ptr, WORD, str));
}