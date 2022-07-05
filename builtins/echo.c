/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:58:26 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/01 23:49:16 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
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

void	echo(t_list *cmd)
{
	int	i;
	int	del;

	i = 0;
	del = 1;
	while (check_arg(cmd->content->args[i]))
		i++;
	if (i != 0)
		del = 0;
	while (cmd->content->args[i])
	{
		printf("%s", cmd->content->args[i]);
		printf(" ");
		i++;
	}
	if (del)
		printf("\n");
}
