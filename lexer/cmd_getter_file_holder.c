/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_getter_file_holder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:18:30 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/20 23:18:31 by ael-mous         ###   ########.fr       */
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
		join_string(&s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == SINGLE_QUOTE)
		{
			join_string(&s, (*this)->c);
			break ;
		}
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
