/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:22:00 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/26 14:47:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_status;

void	main_parent_waiting(int count, t_data **data)
{
	int		i;

	i = 0;
	while (i < (*data)->pip_nb * 2)
		close((*data)->p_fd[i++]);
	i = -1;
	while (++i < count)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
	}
}

void	free_here_fd(t_data **data)
{
	int	i;

	i = 0;
	if ((*data)->here_fd)
	{
		while (i < (*data)->here_size)
			free((*data)->here_fd[i++]);
		free((*data)->here_fd);
		(*data)->here_fd = NULL;
	}
	(*data)->here_size = 0;
}

t_p_line	*initpipeline(void)
{
	t_p_line	*pipeline;

	pipeline = malloc(sizeof(t_p_line));
	pipeline->left = NULL;
	pipeline->left_p = NULL;
	pipeline->right = NULL;
	return (pipeline);
}
