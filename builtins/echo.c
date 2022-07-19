/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:58:26 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/18 23:20:27 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] && str[i] == '-')
		i++;
	else if (str[i] && str[i] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	empty(char *str)
{
	if (str[0] == '\0')
		return (1);
	return (0);
}

void	echo(t_list *cmd)
{
	int	i;
	int	del;

	i = 0;
	del = 1;
	if (cmd->content->args[i])
	{
		while (!empty(cmd->content->args[i]) && check_arg(cmd->content->args[i]))
			i++;
		if (i != 0)
			del = 0;
		//printf("----- here in echo fun----\n");
		while (cmd->content->args[i])
		{
			if (!empty(cmd->content->args[i]))
				printf("%s", cmd->content->args[i]);
			if (cmd->content->args[i + 1])
				printf(" |");
			i++;
		}
		//printf("----- here in echo fun----");
	}
	if (del)
		printf("\n");
	g_status = 0;
}
