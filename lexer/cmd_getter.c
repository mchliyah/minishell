/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:42:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/13 19:42:38 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_s_quote(t_lexer **this)
{
	char	c;
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		c = (*this)->content[(*this)->i + 1];
		if ((*this)->c == SINGLE_QUOTE && (c == SPACE || c == EPIPE
										   || c == LESS || c == GREATER))
		{
			s = join_string(s, (*this)->c);
			break ;
		}
		else if ((*this)->c == SINGLE_QUOTE && (ft_isalnum(c) || c == SPACE))
		{
			while ((*this)->c)
			{
				if ((*this)->c == SPACE || (*this)->c == EPIPE
					|| (*this)->c == LESS || (*this)->c == GREATER)
					return (s);
				s = join_string(s, (*this)->c);
				*this = advance(*this);
			}
		}
	}
	return (s);
}

char	*get_c_word(t_lexer **this)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		if ((*this)->c == L_DOUBLE_QUOTE)
			s = ft_strjoin(s, get_quote_things(this));
		else if ((*this)->c == SINGLE_QUOTE)
			s = ft_strjoin(s, get_s_quote(this));
		else
			s = join_string(s, (*this)->c);
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

char	*cmd_getter(t_lexer **lex)
{
	char	*ptr;

	ptr = NULL;
	if ((*lex)->c == R_DOUBLE_QUOTE)
	{
		ptr = get_quote_things(lex);
		while ((*lex)->content[(*lex)->i + 1] == L_DOUBLE_QUOTE)
		{
			*lex = advance(*lex);
			ptr = ft_strjoin(ptr, get_quote_things(lex));
		}
		if (ft_isalnum((*lex)->content[(*lex)->i + 1]))
		{
			*lex = advance(*lex);
			ptr = ft_strjoin(ptr, get_c_word(lex));
		}
		while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
		{
			*lex = advance(*lex);
			ptr = ft_strjoin(ptr, get_s_quote(lex));
		}
	}
	else if ((*lex)->c == SINGLE_QUOTE)
	{
		ptr = get_s_quote(lex);
		while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
		{
			*lex = advance(*lex);
			ptr = ft_strjoin(ptr, get_quote_things(lex));
		}
		if (ft_isalnum((*lex)->content[(*lex)->i]))
		{
			*lex = advance(*lex);
			ptr = ft_strjoin(ptr, get_c_word(lex));
		}
	}
	else
		ptr = get_c_word(lex);
	return (ptr);
}