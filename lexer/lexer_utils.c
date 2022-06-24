/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/24 22:10:19 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/minishell.h"

t_lexer	*advance(t_lexer *lexer)
{
	lexer->i++;
	lexer->c = lexer->content[lexer->i];
	return (lexer);
}

int	ft_is_symbol(char c)
{
	if (c == EPIPE || c == LESS || c == GREATER || c == SPACE || c == '\0')
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
}*/

/*
  todo	:
 */
char	*get_inside_quotes(t_lexer **it)
{
	char	tmp;
	char	*ptr;
	char	*str;

	ptr = NULL;
	str = NULL;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while ((*it)->c != '\0')
	{
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
		ft_bzero(str, 2);
		str[0] = (*it)->c;
		ptr = ft_strjoin(ptr, str);
		if (!ptr)
			return (NULL);
		free(str);
		str = NULL;
		tmp = (*it)->c;
		*it = advance(*it);
		if ((tmp == SINGLE_QUOTE || tmp == L_DOBLE_QUOTE)
			&& ((*it)->c == SPACE ||  (*it)->c == LESS
				||  (*it)->c == EPIPE ||  (*it)->c == GREATER))
			break;
	}
	return (ptr);
}
t_token *get_char(t_lexer **lex)
{
	int		i;
	char	*ptr;
	char	*str;
	char	*tmp;
//	char **args = NULL;

	i = 0;
	str = NULL;
	if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
	{
		ptr = get_inside_quotes(lex);
	}
	else
	{
		ptr = ft_strdup("");
		if (!ptr)
			return (NULL);
		while ((*lex)->c != '\0')
		{
			str = malloc(2 * sizeof(char));
			if (!str) {
				return (NULL);
			}
			ft_bzero(str, 2);
			str[0] = (*lex)->c;
			ptr = ft_strjoin(ptr, str);
			if (!ptr) {
				return (NULL);
			}
			free(str);
			str = NULL;
			*lex = advance(*lex);
			if ((*lex)->c == SPACE || (*lex)->c == EPIPE || (*lex)->c == LESS
				|| (*lex)->c == GREATER) {
				break;
			}
			else if (((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE) && (*lex)->c != '0')
			{
				tmp = get_inside_quotes(lex);
				ptr = ft_strjoin(ptr, tmp);
				free(tmp);
				break;
			}
		}
	}
//	if (i%2 == 1)
//	{
//		printf("cmd %s   err %c\n", ptr, L_DOBLE_QUOTE);
//		exit(0);
//	}
	// str = check_for_args(lex);
	str = check_for_args(lex, i);
	//check_for_args(lex, i);
	return (init_token(ptr, WORD, str));
}