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

int	check_close_q_arg(t_token *token, int *i)
{
	while (token->arg->content[*i])
	{
		if (token->arg->content[*i] == SINGLE_QUOTE)
			return (true);
		(*i)++;
	}
	return (false);
}

int	check_close_sq_arg(t_token *token, int *i)
{
	while (token->arg->content[*i])
	{
		if (token->arg->content[*i] == R_DOUBLE_QUOTE)
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
	while (token->arg->next)
	{
		i = 0;
		while (token->arg->content[i])
		{
			if (token->arg->content[i] == SINGLE_QUOTE)
			{
				i++;
				if (!check_close_q_arg(token, &i))
				{
					ft_putendl_fd("err unclosed SINGLE QUOTE", STDERR_FILENO);
					return (NULL);
				}
			}
			else if (token->arg->content[i] == L_DOUBLE_QUOTE)
			{
				i++;
				if (!check_close_sq_arg(token, &i))
				{
					ft_putendl_fd("err unclosed DOUBLE QUOTE", STDERR_FILENO);
					return (NULL);
				}
			}
			i++;
		}
		token->arg = token->arg->next;
	}
	token = remove_quoted_args(token, env);
	return (token);
}
