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
			return (true);
		(*i)++;
	}
	return (false);
}

int	check_close_sq_arg(t_token *token, int *a, int *i)
{
	while (token->args[*a][*i])
	{
		if (token->args[*a][*i] == R_DOUBLE_QUOTE)
			return (true);
		(*i)++;
	}
	return (false);
}


/*
 * todo : 1 check for $ signe & join the arr
 *		  2 expend the strings
 *     	  @don't forget the SEGV IN SCAN_ARGS
 *
 */

// !! WARNING: there is a SEGV ls "ds fj ffjaf afja fkja f 'jfd' fj"
t_token	*scan_args(t_token *token, t_pipe_line *env)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	while (token->args[a])
	{
		i = 0;
		while (token->args[a][i])
		{
			if (token->args[a][i] == SINGLE_QUOTE)
			{
				i++;
				if (!check_close_q_arg(token, &a, &i))
				{
					ft_putendl_fd("err unclosed SINGLE QUOTE", STDERR_FILENO);
					return (NULL);
				}
			}
			else if (token->args[a][i] == L_DOUBLE_QUOTE)
			{
				i++;
				if (!check_close_sq_arg(token, &a, &i))
				{
					ft_putendl_fd("err unclosed DOUBLE QUOTE", STDERR_FILENO);
					return (NULL);
				}
			}
//			if (token->args[a][i])
				i++;
		}
		a++;
	}
	token = remove_quoted_args(token, env);
	return (token);
}

t_token	*scan_errs(t_token *token, t_pipe_line *pipe_line)
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
			if (!check_quote(token, &i, &q))
				return (NULL);
		}
		else if (token->content[i] == SINGLE_QUOTE)
			if (!check_s_quote(token, &i, &sq))
				return (NULL);
		i++;
	}
	if (token->args)
	{
		token = scan_args(token, pipe_line);
		if (!token)
			return (NULL);
	}
	if (q != 0)
		return (get_substr(token));
	else if (sq != 0)
		return (get_substr_single_quotes(token));
	return (token);
}
