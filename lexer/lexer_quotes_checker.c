/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:45:35 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/10 19:58:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quote(t_token *token, int *i)
{
	int	q;

	(*i)++;
	q = 1;
	while (token->content[*i] != L_DOUBLE_QUOTE
		&& token->content[*i] != '\0')
		(*i)++;
	if (token->content[*i] == R_DOUBLE_QUOTE)
		q++;
	if (q % 2 != 0 && token->content[*i] == '\0')
	{
		printf("err alm3lam sad l quotes\n");
		return (false);
	}
	return (true);
}

int	check_s_quote(t_token *token, int *i)
{
	int	sq;

	(*i)++;
	sq = 1;
	while (token->content[*i] != SINGLE_QUOTE
		&& token->content[*i] != '\0')
	{
		(*i)++;
	}
	if (token->content[*i] == SINGLE_QUOTE)
		sq++;
	if (sq % 2 != 0 && token->content[*i] == '\0')
	{
		printf("err alm3lam sad l single quotes\n");
		return (false);
	}
	return (true);
}

bool	scan_errs(t_token **token, t_env *env, int was_rd)
{
	t_arg	*tmp;
	int		i;

	i = 0;
	while ((*token)->content[i])
	{
		if ((*token)->content[i] == L_DOUBLE_QUOTE)
		{
			if (!check_quote((*token), &i))
				return (NULL);
		}
		else if ((*token)->content[i] == SINGLE_QUOTE)
			if (!check_s_quote((*token), &i))
				return (false);
		i++;
	}
	tmp = (*token)->arg;
	if (tmp)
	{
		if (!scan_args(&(*token)->arg, env))
			return (NULL);
	}
	scan_vars((*token), env, was_rd);
	return (true);
}
