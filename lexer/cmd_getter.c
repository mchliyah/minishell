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

//		c = (*this)->content[(*this)->i + 1];
//		if ((*this)->c == SINGLE_QUOTE && (c == SPACE || c == EPIPE
//										   || c == LESS || c == GREATER))
//		{
//			s = join_string(s, (*this)->c);
//			break ;
//		}
//		else if ((*this)->c == SINGLE_QUOTE && (ft_isalnum(c) || c == SPACE))
//		{
//			while ((*this)->c)
//			{
//				if ((*this)->c == SPACE || (*this)->c == EPIPE
//					|| (*this)->c == LESS || (*this)->c == GREATER)
//					return (s);
//				s = join_string(s, (*this)->c);
//				*this = advance(*this);
//			}
//		}
char	*get_s_quote(t_lexer **this)
{
//	char	c;
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
//  "''"'"$USER"'"''"

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
		if ((*lex)->c == EPIPE || (*lex)->c == LESS
			||  (*lex)->c == GREATER || (*lex)->c == SPACE)
		{
			if ((*lex)->c == SPACE)
				*lex = advance(*lex);
			break ;
		}
		if ((*lex)->c != '\0')
			*lex = advance(*lex);
		if ((*lex)->c == EPIPE || (*lex)->c == LESS
			||  (*lex)->c == GREATER || (*lex)->c == SPACE)
		{
			if ((*lex)->c == SPACE)
				*lex = advance(*lex);
			break ;
		}
	}
	return (ptr);
}

//char	*cmd_getter(t_lexer **lex)
//{
//	char	*ptr;
//
//	ptr = NULL;
//	if ((*lex)->c == R_DOUBLE_QUOTE)
//	{
//		ptr = get_quote_things(lex);
//		if ((*lex)->c != '\0')
//			*lex = advance(*lex);
//		while ((*lex)->c == L_DOUBLE_QUOTE)
//		{
//			ptr = ft_strjoin(ptr, get_quote_things(lex));
//			if ((*lex)->c != '\0')
//				*lex = advance(*lex);
//		}
//		if (ft_isalnum((*lex)->c))
//		{
//			ptr = ft_strjoin(ptr, get_c_word(lex));
//			//*lex = advance(*lex);
//		}
//		while ((*lex)->c == SINGLE_QUOTE)
//		{
//			ptr = ft_strjoin(ptr, get_s_quote(lex));
//			if ((*lex)->c != '\0')
//				*lex = advance(*lex);
//		}
//	}
//	else if ((*lex)->c == SINGLE_QUOTE)
//	{
//		ptr = get_s_quote(lex);
//		if ((*lex)->c != '\0')
//			*lex = advance(*lex);
//		while ((*lex)->c == SINGLE_QUOTE)
//		{
//			ptr = ft_strjoin(ptr, get_quote_things(lex));
//			if ((*lex)->c != '\0')
//				*lex = advance(*lex);
//		}
//		if (ft_isalnum((*lex)->c))
//		{
//			if ((*lex)->c != '\0')
//				*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_c_word(lex));
//		}
//	}
//	else
//		ptr = get_c_word(lex);
//	return (ptr);
//}