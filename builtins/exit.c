/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/03 23:01:04 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '9' || str[i] <= '0')
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(t_list *cmd, t_data **data)
{
	t_arg	*args;

	args = cmd->content->arg;
	if (args && args->next)
	{
		g_status = 1;
		ft_putstr_fd("minishell: exit: arguments error", 2);
	}
	else if (args && !str_isnum(args->content))
	{
		g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->content, 2);
		ft_putendl_fd(": put numeric arg", 2);
	}
	else if (args)
		g_status = ft_atoi(args->content);
	(*data)->exit = 1;
}
