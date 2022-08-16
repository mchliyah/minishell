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

int	cmd_checker(t_lexer **lex)
{
	if ((*lex)->c == EPIPE || (*lex)->c == LESS
		|| (*lex)->c == GREATER || (*lex)->c == SPACE)
	{
		while ((*lex)->c == SPACE)
			*lex = advance(*lex);
		return (1);
	}
	if ((*lex)->c != '\0')
		*lex = advance(*lex);
	if ((*lex)->c == EPIPE || (*lex)->c == LESS
		|| (*lex)->c == GREATER || (*lex)->c == SPACE)
	{
		while ((*lex)->c == SPACE)
			*lex = advance(*lex);
		return (1);
	}
	return (0);
}

char	*cmd_getter(t_lexer **lex)
{
	char	*ptr;
	char	*s;

	ptr = ft_strdup("");
	if (!ptr)
	{
		perror("malloc");
		exit(1);
	}
	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	while ((*lex)->c != '\0')
	{
		if ((*lex)->c == L_DOUBLE_QUOTE)
			s = get_quote_things(lex);
		else if ((*lex)->c == SINGLE_QUOTE)
			s = get_s_quote(lex);
		else
			s = get_c_word(lex);
		ptr = ft_strjoin(ptr, s);
		if (cmd_checker(lex))
			break ;
	}
	return (ptr);
}
