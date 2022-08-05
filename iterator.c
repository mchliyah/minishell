/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/27 19:57:27 by ael-mous         ###   ########.fr       */
/*                                                                           */
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
//	{
//		printf(":cmd0 %s\n", this_pipe->left->content->content);
//		if (this_pipe->left->content->arg)
//			while (this_pipe->left->content->arg)
//			{
//				printf("%s\n", this_pipe->left->content->arg->content);
//				this_pipe->left->content->arg = this_pipe->left->content->arg->next;
//			}
//	}
	(*exec)->cmd_i++;
	(*exec)->p_in += 2;
	return (0);
	if (this_pipe->right)
		exec_cmd(this_pipe->right, envp, exec);
//	{
//		printf(":cmd1 %s\n", this_pipe->right->content->content);
//		if (this_pipe->right->content->arg)
//			while (this_pipe->right->content->arg)
//			{
//				printf("%s\n", this_pipe->right->content->arg->content);
//				this_pipe->right->content->arg = this_pipe->right->content->arg->next;
//			}
//	}
}


int	iterator(t_pipe_line *this_pipe, char **envp, t_data **exec)
{
	if (this_pipe->left_p)
		iterator(this_pipe->left_p, envp, exec);
//	printf("cmd %s\n", this_pipe)
	execute_childes(this_pipe, envp, exec);
	return (EXIT_SUCCESS);
}
