/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:38:59 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/04 21:40:33 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**arr_arg(t_list *cmd)
{
	char	**args;
	t_arg	*track;
	t_arg	*track1;
	int		i;

	i = 0;
	track = cmd->content->arg;
	while (track)
	{
		track = track->next;
		i++;
	}
	args = malloc(sizeof(char *) * (i + 2));
	args[0] = cmd->content->content;
	i = 1;
	track1 = cmd->content->arg;
	while (track1)
	{
		args[i++] = track1->content;
		track1 = track1->next;
	}
	args[i] = NULL;
	return (args);
}
