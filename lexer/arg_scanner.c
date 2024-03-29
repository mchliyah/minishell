/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_scanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:38:41 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 21:35:52 by mchliyah         ###   ########.fr       */
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

int	scan_args_staff(t_arg *token, int i)
{
	while (token->content[i])
	{
		if (token->content[i] == SINGLE_QUOTE)
		{
			i++;
			if (!check_close_q_arg(token, &i))
			{
				ft_putendl_fd("Error unclosed SINGLE QUOTE", STDERR_FILENO);
				return (1);
			}
		}
		else if (token->content[i] == L_DOUBLE_QUOTE)
		{
			i++;
			if (!check_close_sq_arg(token, &i))
			{
				ft_putendl_fd("Error unclosed DOUBLE QUOTE", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	scan_args(t_arg **arg, t_env *env)
{
	t_arg	*token;
	int		i;

	token = *arg;
	while (token)
	{
		i = 0;
		if (scan_args_staff(token, i) == 1)
			return (false);
		token = token->next;
	}
	*arg = remove_quoted_args(*arg, env);
	return (true);
}
