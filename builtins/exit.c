/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/22 22:45:09 by mchliyah         ###   ########.fr       */
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

void	exit_cmd(t_pipe_line *p_line)
{
	char	*args0;

	args0 = p_line->left->content->args[0];
	p_line->exit = 1;
	if (args0 && p_line->left->content->args[1])
	{
		printf("salkfjdlskfj\n");
		g_status = 1;
		ft_putstr_fd("minishell: exit: arguments error", 2);
	}
	else if (args0 && !str_isnum(args0))
	{
		g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args0, 2);
		ft_putendl_fd(": put numeric arg", 2);
	}
	else if (args0)
		g_status = ft_atoi(args0);
}
