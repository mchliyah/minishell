/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 11:53:53 by mchliyah         ###   ########.fr       */
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

void	exit_cmd(t_list *p_line)
{
	t_arg	*args;

	args = p_line->content->arg;
//	(*p_line)->exit = 1;
	if (args && args->next)
	{
		// g_status = 1;
		ft_putstr_fd("minishell: exit: arguments error", 2);
	}
	else if (args && !str_isnum(args->content))
	{
		// g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->content, 2);
		ft_putendl_fd(": put numeric arg", 2);
	}
	// else if (args)
	// 	g_status = ft_atoi(args->content);
}
