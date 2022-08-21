/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/18 00:41:18 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	str_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	exit_cmd(t_list *cmd)
{
	t_arg	*args;

	args = cmd->content->arg;
	if (args && str_isnum(args->content) && args->next)
	{
		g_status = 1;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd(": too many arguments", 2);
		return (0);
	}
	else if (args && !args->next && !ft_strcmp(args->content, "--"))
		return (1);
	else if (args && !str_isnum(args->content))
	{
		g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->content, 2);
		ft_putendl_fd(": put numeric arg", 2);
	}
	else if (args)
		g_status = ft_atoi(args->content);
	return (1);
}
