/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_scanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:38:41 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/19 16:38:44 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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

// !! WARNING: there is a SEGV ls "ds fj ffjaf afja fkja f 'jfd' fj"
t_token	*scan_args(t_token *token, t_env *env)
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
			i++;
		}
		a++;
	}
	token = remove_quoted_args(token, env);
	return (token);
}
