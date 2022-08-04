/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:58:26 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/04 21:40:58 by mchliyah         ###   ########.fr       */
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
	if ((size_t)str < 1000)
		return (1);
	if (str[0] == '\0')
		return (1);
	return (0);
}

void	echo(t_list *cmd)
{
	int		i;
	int		del;
	char	**args;

	i = 1;
	del = 1;
	args = arr_arg(cmd);
	if (cmd->content->arg)
	{
		while (!empty(args[i])
			&& check_arg(args[i]))
			i++;
	}
	if (i != 1)
		del = 0;
	while (args[i])
	{
		if (!empty(args[i]))
			printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (del)
		printf("\n");
	free (args);
}
