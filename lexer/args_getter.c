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
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == SINGLE_QUOTE)
		{
			s = join_string(s, (*this)->c);
			break ;
		}
	}
	return (s);
}

char	*get_s_quote_things(t_lexer **this)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == L_DOUBLE_QUOTE)
		{
			s = join_string(s, (*this)->c);
			break ;
		}
	}
	return (s);
}

char	*get_s_word(t_lexer **this)
{
	char	tmp;
	char	*s;

	s = ft_strdup("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		tmp = (*this)->content[(*this)->i + 1];
		if (((*this)->c == SPACE && (tmp == L_DOUBLE_QUOTE || tmp == EOS))
			|| (*this)->c == SINGLE_QUOTE || (*this)->c == EPIPE
			|| (*this)->c == REDIRECT_IN || (*this)->c == REDIRECT_OUT
			|| (*this)->c == SPACE || (*this)->c == EOS)
		{
			if ((*this)->c == L_DOUBLE_QUOTE && tmp == EOS)
				s = join_string(s, (*this)->c);
			break ;
		}
	}
	return (s);
}
