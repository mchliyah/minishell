/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 22:23:33 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_l_quote(t_lexer **lex, char	*ptr)
{
	char	*save;
	char	*tmp;

	ptr = get_quote_things(lex);
	while ((*lex)->content[(*lex)->i + 1] == L_DOUBLE_QUOTE)
	{
		*lex = advance(*lex);
		save = get_quote_things(lex);
		tmp = ft_strjoin(ptr, save);
		free_strjoin(&ptr, &save);
		ptr = tmp;
	}
	if (check_spectial_char(lex))
	{
		*lex = advance(*lex);
		save = get_s_word(lex);
		tmp = ft_strjoin(ptr, save);
		free_strjoin(&ptr, &save);
		ptr = tmp;
	}
	while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
		ft_single(lex, &ptr);
	return (ptr);
}

void	ft_double_q(t_lexer **lex, char **ptr)
{
	char	*qstr;
	char	*save;

	*lex = advance(*lex);
	qstr = get_quote_things(lex);
	save = ft_strjoin(*ptr, qstr);
	free_strjoin(ptr, &qstr);
	*ptr = save;
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
			ft_double_q(lex, &ptr);
		if (ft_isalnum((*lex)->content[(*lex)->i]))
		{
			*lex = advance(*lex);
			qstr = get_s_word(lex);
			save = ft_strjoin(ptr, qstr);
			free_strjoin(&ptr, &qstr);
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
		if (!ft_space_advacer(lex))
			break ;
		if ((*lex)->c == EPIPE || (*lex)->c == LESS || (*lex)->c == GREATER)
			break ;
		s = check_for_args(lex);
		if (!s)
			return (NULL);
		if (!opt)
			opt = list_new(s);
		else
			list_add_back(&opt, list_new(s));
		if ((*lex)->c == EPIPE || (*lex)->c == LESS || (*lex)->c == GREATER)
			break ;
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
