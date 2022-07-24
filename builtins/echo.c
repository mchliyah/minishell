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
	if (cmd->content->arg->content)
	{
		while (!empty(cmd->content->arg->content)
			&& check_arg(cmd->content->arg->content))
		{
			cmd->content->arg = cmd->content->arg->next;
			i++;
		}
		if (i != 0)
			del = 0;
		//printf("----- here in echo fun----\n");
		while (cmd->content->arg->content)
		{
			if (!empty(cmd->content->arg->content))
				printf("%s", cmd->content->arg->content);
			if (cmd->content->arg->next->content)
				printf(" |");
		}
		//printf("----- here in echo fun----");
	}
	if (del)
		printf("\n");
	g_status = 0;
}
