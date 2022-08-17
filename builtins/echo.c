/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:58:26 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/10 20:13:05 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] && str[i] == '-' && str[i + 1] == 'n')
		i++;
	else if (str[i] && (str[i] != '-' || (str[i] == '-' && str[i + 1] != 'n')))
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
		while (!empty(args[i]) && check_arg(args[i]))
			i++;
	if (i != 1)
		del = 0;
	while (args[i])
	{
		if (!empty(args[i]))
			printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (del)
		printf("\n");
	g_status = 0;
	free (args);
}
