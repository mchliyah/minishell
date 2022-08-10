/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:45:35 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/19 13:15:22 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_substr(t_token *token, t_env *env)
{
	char	*ptr;
	int		j;
	char	**str;

	if (check_for_variables(token->content))
		return (scan_vars(token, env));
	j = 0;
	str = ft_split(token->content, '\"');
	ptr = ft_strdup("");
	while (str[j])
	{
		ptr = ft_strjoin(ptr, str[j]);
		free(str[j]);
		j++;
	}
	token->content = ptr;
	return (token);
}

int	check_quote(t_token *token, int *i, int *q)
{
	(*i)++;
	(*q)++;
	while (token->content[*i] != L_DOUBLE_QUOTE
		&& token->content[*i] != '\0')
		(*i)++;
	if (token->content[*i] == R_DOUBLE_QUOTE)
		(*q)++;
	if (*q % 2 != 0 && token->content[*i] == '\0')
	{
		printf("err alm3lam sad l quotes\n");
		return (false);
		// ! should free here
	}
	return (true);
}

int	check_s_quote(t_token *token, int *i, int *sq)
{
	(*i)++;
	(*sq)++;
	while (token->content[*i] != SINGLE_QUOTE
		&& token->content[*i] != '\0')
	{
		(*i)++;
	}
	if (token->content[*i] == SINGLE_QUOTE)
		(*sq)++;
	if (*sq % 2 != 0 && token->content[*i] == '\0')
	{
		printf("err alm3lam sad l single quotes\n");
		return (false);
		// ! should free here
	}
	return (true);
}

// protect of split
t_token	*get_substr_single_quotes(t_token *token)
{
	char	*ptr;
	int		j;
	char	**str;

	j = 0;
	if (token->content[j] == '$' && token->content[j + 1] == SINGLE_QUOTE)
		j++;
	str = ft_split(token->content, '\'');
	ptr = ft_strdup("");
	while (str[j])
	{
		ptr = ft_strjoin(ptr, str[j]);
		free(str[j]);
		j++;
	}
	free(token->content);
	token->content = ptr;
	return (token);
}


t_token	*scan_errs(t_token *token, t_env *env)
{
	t_arg	*tmp;
	int		q;
	int		sq;
	int		i;

	i = 0;
	q = 0;
	sq = 0;
	while (token->content[i])
	{
		if (token->content[i] == L_DOUBLE_QUOTE)
		{
			if (!check_quote(token, &i, &q))
				return (NULL);
		}
		else if (token->content[i] == SINGLE_QUOTE)
			if (!check_s_quote(token, &i, &sq))
				return (NULL);
		i++;
	}
	tmp = token->arg;
	if (tmp)
	{
		token->arg = scan_args(tmp, env);
		if (!token->arg)
			return (NULL);
	}
	scan_vars(token, env);
	/*
	if (q != 0 || (check_for_variables(token->content)
			&& !ft_strchr(token->content, SINGLE_QUOTE)))
		return (get_substr(token, env));
	else if (sq != 0)
		return (get_substr_single_quotes(token));
	 */
	return (token);
}
