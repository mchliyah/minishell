/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:45:35 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/01 11:45:40 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdbool.h>
t_token	*get_substr(t_token *token)
{
	char	*ptr;
	int		j;
	char	**str;

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

int	get_quote(t_token *token, int *i, int *q)
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

int	get_s_quote(t_token *token, int *i, int *sq)
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

int	check_close_q_arg(t_token *token, int *a, int *i)
{
	while (token->args[*a][*i])
	{
		if (token->args[*a][*i] == SINGLE_QUOTE)
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_close_sq_arg(t_token *token, int *a, int *i)
{
	while (token->args[*a][*i])
	{
		if (token->args[*a][*i] == R_DOUBLE_QUOTE)
			return (1);
		(*i)++;
	}
	return (0);
}

int	is_there_squote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == SINGLE_QUOTE)
			return (true);
	}
	return (false);
}

int	is_there_quote(char *arg) {
	int i;

	i = -1;
	while (arg[++i]) {
		if (arg[i] == L_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}

char	*rm_quote(char *arg)
{
	int	i  = -1;
	char	**tmp;

	tmp = ft_split(arg, '\"');
	free(arg);
	while (tmp[++i])
	{
		printf("%s", tmp[i]);
	}
	return arg;
}

/* args = hello "$user" "$"user.jf
 *  step 1 =
 */
t_token *remove_quoted_args(t_token *token)
{
	int a;
	//int i;

	a = 0;
	while (token->args[a])
	{
		if (is_there_quote(token->args[a]))
			rm_quote(token->args[a]);
//		else if (is_there_squote(token->args[a]))
//			rm_sqoute(token->args[a]);
	}
	return token;
}

t_token	*scan_args(t_token *token)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	// split "$user"
	while (token->args[a])
	{
		i = 0;
		while (token->args[a][i])
		{
			if (token->args[a][i] == SINGLE_QUOTE)
			{
				if (!check_close_q_arg(token, &a, &i))
					return (NULL);
			}
			else if (token->args[a][i] == L_DOUBLE_QUOTE)
		{
				if (!check_close_sq_arg(token, &a, &i))
					return (NULL);
			}
			if (token->args[a][i])
				i++;
		}
		if (token->args[a])
			a++;
	}
	token = remove_quoted_args(token);
	return (token);
}

t_token	*scan_errs(t_token *token)
{
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
			if (get_quote(token, &i, &q) == 1)
				return (NULL);
		}
		else if (token->content[i] == SINGLE_QUOTE)
			if (get_s_quote(token, &i, &sq) == 1)
				return (NULL);
		i++;
	}
	if (token->args)
		token = scan_args(token);
	if (q != 0)
		return (get_substr(token));
	else if (sq != 0)
		return (get_substr_single_quotes(token));
	return (token);
}
