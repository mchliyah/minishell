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

void	ft_double_q(t_lexer **this, char **s)
{
	char	*save;
	char	*tmp;

	tmp = get_quote_things(this);
	save = ft_strjoin(*s, tmp);
	free_strjoin(s, &tmp);
	*s = save;
}

void	ft_single_q(t_lexer **this, char **s)
{
	char	*save;
	char	*tmp;

	tmp = get_s_quote(this);
	save = ft_strjoin(*s, tmp);
	free_strjoin(s, &tmp);
	*s = save;
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
			ft_double_q(this, &s);
		else if ((*this)->c == SINGLE_QUOTE)
			ft_single_q(this, &s);
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

void	ft_cmd_getter_norm_helper(char **s, t_lexer **lex)
{
	if ((*lex)->c == L_DOUBLE_QUOTE)
		*s = get_quote_things(lex);
	else if ((*lex)->c == SINGLE_QUOTE)
		*s = get_s_quote(lex);
	else
		*s = get_c_word(lex);
}

char	*cmd_getter(t_lexer **lex)
{
	char	*ptr;
	char	*tmp;
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
		ft_cmd_getter_norm_helper(&s, lex);
		tmp = ft_strjoin(ptr, s);
		free(ptr);
		ptr = tmp;
		free(s);
		if (cmd_checker(lex))
			break ;
	}
	return (ptr);
}
