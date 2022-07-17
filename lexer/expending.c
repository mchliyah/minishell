/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:41:01 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/15 12:41:03 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	is_there_quote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == L_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}


bool	check_for_variables(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (true);
	}
	return (false);
}

char	*rm_quote(char *arg, t_pipe_line *env)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == L_DOUBLE_QUOTE && arg[i + 1] == '$')
		{
			i++;
			if (arg[i + 1] == R_DOUBLE_QUOTE)
				return (get_simple_word(arg));
		}
		else
			return (get_variable(arg, env));
		i++;
	}
	return NULL;
}

t_token	*remove_quoted_args(t_token *token, t_pipe_line *env)
{
	int	a;
	//int i;
	a = 0;
	while (token->args[a])
	{
		if (is_there_quote(token->args[a]))
			rm_quote(token->args[a], env);
//		else if (is_there_squote(token->args[a]))
//			rm_sqoute(token->args[a]);
		a++;
	}
	return token;
}