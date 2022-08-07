/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:53:24 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/04 12:53:26 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_quote_things(t_lexer **this)
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
		if ((*this)->c == R_DOUBLE_QUOTE && (c == SPACE || c == EPIPE
				|| c == LESS || c == GREATER))
		{
			s = join_string(s, (*this)->c);
			break ;
		}
//		else if ((*this)->c == L_DOUBLE_QUOTE && ft_isalnum(c))
//		{
//			HERE ;
//			*this = advance(*this);
//			s = ft_strjoin(s, get_s_word(this));
//			break ;
//		}
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
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		c = (*this)->content[(*this)->i + 1];
		if ((*this)->c == SINGLE_QUOTE)
			//&& (c == SPACE || c == EPIPE
			//	|| c == LESS || c == GREATER))
		{
			s = join_string(s, (*this)->c);
			break ;
		}
		else if ((*this)->c == SINGLE_QUOTE && ft_isalnum(c))
		{
			HERE ;
			s = ft_strjoin(s, get_s_word(this));
			break ;
		}
	}
	return (s);
}
//		if (((*this)->c == SPACE && (tmp == L_DOUBLE_QUOTE || tmp == EOS))
//			|| (*this)->c == SINGLE_QUOTE || (*this)->c == EPIPE
//			|| (*this)->c == REDIRECT_IN || (*this)->c == REDIRECT_OUT
//			|| (*this)->c == SPACE || (*this)->c == EOS)
//		{
//			if ((*this)->c == L_DOUBLE_QUOTE && tmp == EOS)
//				s = join_string(s, (*this)->c);
//			break ;
//		}

char	*get_s_word(t_lexer **this)
{
	char	tmp;
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		tmp = (*this)->content[(*this)->i + 1];
		if (ft_isprint((*this)->c) && tmp == L_DOUBLE_QUOTE)
			s = ft_strjoin(s, get_quote_things(this));
		else if (ft_isprint((*this)->c) && tmp == SINGLE_QUOTE)
			s = ft_strjoin(s, get_s_quote_things(this));
		else
			s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == EPIPE || (*this)->c == LESS
			|| (*this)->c == GREATER || (*this)->c == SPACE)
			break ;
	}
	return (s);
}
