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

int	check_close_q_arg(t_arg *token, int *i)
{
	while (token->content[*i])
	{
		if (token->content[*i] == SINGLE_QUOTE)
			return (true);
		(*i)++;
	}
	return (false);
}

int	check_close_sq_arg(t_arg *token, int *i)
{
	while (token->content[*i])
	{
		if (token->content[*i] == R_DOUBLE_QUOTE)
			return (true);
		(*i)++;
	}
	return (false);
}

// !! WARNING: there is a SEGV ls "ds fj ffjaf afja fkja f 'jfd' fj"
t_arg	*scan_args(t_arg *arg, t_env *env)
{
	t_arg	*token;
	int		i;

	i = 0;
	token = arg;
	while (token)
	{
		printf("arg_token %s\n", token->content);
		i = 0;
		while (token->content[i])
		{
			if (token->content[i] == SINGLE_QUOTE)
			{
				i++;
				if (!check_close_q_arg(token, &i))
				{
					ft_putendl_fd("err unclosed SINGLE QUOTE", STDERR_FILENO);
					return (NULL);
				}
			}
			else if (token->content[i] == L_DOUBLE_QUOTE)
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
		token = token->next;
	}
	token = arg;
	arg = remove_quoted_args(token, env);
	return (arg);
}
