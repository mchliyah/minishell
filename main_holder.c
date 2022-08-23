/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:22:00 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/23 19:30:50 by mchliyah         ###   ########.fr       */
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
	while (i < (*data)->here_size)
		free((*data)->here_fd[i++]);
	if ((*data)->here_size)
		free((*data)->here_fd);
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
