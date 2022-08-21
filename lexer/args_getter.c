/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:53:24 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/10 19:55:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_quote_things(t_lexer **this)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		join_string(&s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == R_DOUBLE_QUOTE)
		{
			join_string(&s, (*this)->c);
			break ;
		}
	}
	return (s);
}

int	norm_heleper1(t_lexer **this, char **s)
{
	while ((*this)->c)
	{
		if ((*this)->c == SPACE || (*this)->c == EPIPE
			|| (*this)->c == LESS || (*this)->c == GREATER)
		{
			return (false);
		}
		join_string(s, (*this)->c);
		*this = advance(*this);
	}
	return (1);
}

char	*get_s_quote_things(t_lexer **this)
{
	char	c;
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		join_string(&s, (*this)->c);
		*this = advance(*this);
		c = (*this)->content[(*this)->i + 1];
		if ((*this)->c == SINGLE_QUOTE && (c == SPACE || c == EPIPE
				|| c == LESS || c == GREATER))
		{
			join_string(&s, (*this)->c);
			break ;
		}
		else if ((*this)->c == SINGLE_QUOTE && (ft_isalnum(c) || c == SPACE))
			if (!norm_heleper1(this, &s))
				return (s);
	}
	return (s);
}

void	get_s_word_norm_helper(t_lexer **this, char **s)
{
	char	*save;
	char	*tmp;

	if ((*this)->c == L_DOUBLE_QUOTE)
	{
		save = get_quote_things(this);
		tmp = ft_strjoin(*s, save);
		free_strjoin(s, &save);
		*s = tmp;
	}
	else if ((*this)->c == SINGLE_QUOTE)
	{
		save = get_s_quote_things(this);
		tmp = ft_strjoin(*s, save);
		free_strjoin(s, &save);
		*s = tmp;
	}
}

//		{
//			save = get_quote_things(this);
//			tmp = ft_strjoin(s, save);
//			free_strjoin(&s, &save);
//			s = tmp;
//		}
//		else if ((*this)->c == SINGLE_QUOTE)
//		{
//			save = get_s_quote_things(this);
//			tmp = ft_strjoin(s, save);
//			free_strjoin(&s, &save);
//			s = tmp;
//		}
char	*get_s_word(t_lexer **this)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		exit(1);
	while ((*this)->c != '\0')
	{
		if ((*this)->c == L_DOUBLE_QUOTE || (*this)->c == SINGLE_QUOTE)
			get_s_word_norm_helper(this, &s);
		else
			join_string(&s, (*this)->c);
		if ((*this)->c == EPIPE || (*this)->c == LESS
			|| (*this)->c == GREATER || (*this)->c == SPACE)
			break ;
		*this = advance(*this);
		if ((*this)->c == EPIPE || (*this)->c == LESS
			|| (*this)->c == GREATER || (*this)->c == SPACE)
			break ;
	}
	return (s);
}
