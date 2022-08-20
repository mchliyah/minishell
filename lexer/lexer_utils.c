/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/19 21:40:16 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	join_string(char **ptr, char c)
{
	char	*j_str;
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		exit(1);
	ft_bzero(str, 2);
	str[0] = c;
	j_str = ft_strjoin(*ptr, str);
	if (!j_str)
		exit(1);
	free(str);
	free(*ptr);
	*ptr = j_str;
}

// leaks !!
char	*get_l_quote(t_lexer **lex, char	*ptr)
{
	ptr = get_quote_things(lex);
	while ((*lex)->content[(*lex)->i + 1] == L_DOUBLE_QUOTE)
	{
		*lex = advance(*lex);
		ptr = ft_strjoin(ptr, get_quote_things(lex));
	}
	if (ft_isprint((*lex)->content[(*lex)->i + 1])
		&& (*lex)->content[(*lex)->i + 1] != EPIPE
		&& (*lex)->content[(*lex)->i + 1] != LESS
		&& (*lex)->content[(*lex)->i + 1] != GREATER
		&& (*lex)->content[(*lex)->i + 1] != SPACE)
	{
		*lex = advance(*lex);
		ptr = ft_strjoin(ptr, get_s_word(lex));
	}
	while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
	{
		*lex = advance(*lex);
		ptr = ft_strjoin(ptr, get_s_quote_things(lex));
	}
	return (ptr);
}

char	*check_for_args(t_lexer **lex)
{
	char	*save;
	char	*qstr;
	char	*ptr;

	ptr = NULL;
	if ((*lex)->c == R_DOUBLE_QUOTE)
		ptr = get_l_quote(lex, ptr);
	else if ((*lex)->c == SINGLE_QUOTE)
	{
		ptr = get_s_quote_things(lex);
		while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
		{
			*lex = advance(*lex);
			qstr = get_quote_things(lex);
			save = ft_strjoin(ptr, qstr);
			free(ptr);
			free(qstr);
			ptr = NULL;
			qstr = NULL;
			ptr = save;
		}
		if (ft_isalnum((*lex)->content[(*lex)->i]))
		{
			*lex = advance(*lex);
			qstr = get_s_word(lex);
			save = ft_strjoin(ptr, qstr);
			free(ptr);
			free(qstr);
			ptr = NULL;
			qstr = NULL;
			ptr = save;
		}
	}
	else
		ptr = get_s_word(lex);
	return (ptr);
}

t_arg	*get_args(t_lexer **lex)
{
	char	*s;
	t_arg	*opt;

	opt = NULL;
	while ((*lex)->c != '\0')
	{
		if ((*lex)->c == SPACE)
		{
			while ((*lex)->c == SPACE)
				*lex = advance(*lex);
			if ((*lex)->c == EOS)
				break ;
		}
		if ((*lex)->c == EPIPE || (*lex)->c == LESS || (*lex)->c == GREATER)
			break ;
		s = check_for_args(lex);
		if (!s)
			return (NULL);
		if (!opt)
			opt = list_new(s);
		else
			list_add_back(&opt, list_new(s));
		if ((*lex)->c != '\0')
			*lex = advance(*lex);
	}
	return (opt);
}

t_token	*get_char(t_lexer **lex, int was_rd)
{
	char	*ptr;

	ptr = cmd_getter(lex);
	if (was_rd)
	{
		return (init_token(ptr, WORD, NULL));
	}
	return (init_token(ptr, WORD_CMD, get_args(lex)));
}
