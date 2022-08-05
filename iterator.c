/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/05 18:34:12 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

	/*
	 *  left    output to 1   |_0_|_1_|
	 *  right input form 0 and output to 1 if there is no out redirection
	 *
	 *   cmd[0]    |  cmd[1]   |   cmd[2]
	 *   |_x_|_1_| - |_0_|_3_| - |_x_|_2_|
	 *  4          2
	 */
//void	parent_orders(t_data *exec)
//{
//	int	i;
//
//	while (i < exec->p_in)
//	{
//		close(exec->p_fd[i]);
//		i++;
//	}
//	waitpid(-1, NULL, 0);
//}

int	execute_childes(t_pipe_line *this_pipe, char **envp, t_data **exec)
{
	if (this_pipe->left)
		exec_cmd(this_pipe->left, envp, exec);
	(*exec)->cmd_i++;
	(*exec)->p_in += 2;
	if (this_pipe->right)
		exec_cmd(this_pipe->right, envp, exec);
	return (0);
}


int	iterator(t_pipe_line *this_pipe, char **envp, t_data **exec)
{
	if (this_pipe->left_p)
		iterator(this_pipe->left_p, envp, exec);
	execute_childes(this_pipe, envp, exec);
	return (EXIT_SUCCESS);
}
