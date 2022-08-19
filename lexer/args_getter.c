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
		{
			while ((*this)->c)
			{
				if ((*this)->c == SPACE || (*this)->c == EPIPE
					|| (*this)->c == LESS || (*this)->c == GREATER)
					return (s);
				join_string(&s, (*this)->c);
				*this = advance(*this);
			}
		}
	}
	return (s);
}

// *leaks
char	*get_s_word(t_lexer **this)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		exit(1);
	while ((*this)->c != '\0')
	{
		if ((*this)->c == L_DOUBLE_QUOTE)
			s = ft_strjoin(s, get_quote_things(this));
		else if ((*this)->c == SINGLE_QUOTE)
			s = ft_strjoin(s, get_s_quote_things(this));
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
