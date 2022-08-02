/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/27 19:57:27 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"




//t_exec	*exec_attr(t_exec *exec)
//{
////	exec->p_index += 2;
//	return (exec);
//}
	/*
	 *  left    output to 1   |_0_|_1_|
	 *  right input form 0 and output to 1 if there is no out redirection
	 *
	 *   cmd[0]    |  cmd[1]   |   cmd[2]
	 *   |_x_|_1_| - |_0_|_3_| - |_x_|_2_|
	 *  4          2
	 */
void	parent_orders(t_data *exec)
{
	int	i;

	while (i < exec->p_in)
	{
		close(exec->p_fd[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
}
void	execute_childes(t_pipe_line *this_pipe, char **envp, t_data *exec)
{
	printf("____________p_index %d\n", exec->p_in);
	if (this_pipe->left)
	{
		if (fork() == -1)
		{
			perror("fork(): ");
			return ;
		}
		printf("l---------%s----------\n", this_pipe->left->content->content);
		exec_cmd(this_pipe->left, envp, exec);
		exec->cmd_i++;
		return ;
	}
	exec->p_in += 2;
	if (this_pipe->right)
	{
		if (fork() == -1)
		{
			perror("fork(): ");
			return ;
		}
		printf("r---------%s----------\n", this_pipe->right->content->content);
		dup2(fd[0], 0);
		exec_cmd(this_pipe->right, envp, exec);
		exec->cmd_i++;
	}
	parent_orders(exec);
}

/*
 * closing fds if pipe failed
 */
int	iterator(t_pipe_line *this_pipe, char **envp, t_data *exec)
{
	int	i;
	int	j;

	if (this_pipe->left_p)
	{
		iterator(this_pipe->left_p, envp, exec);
	}
	execute_childes(this_pipe, envp, exec);
	return (EXIT_SUCCESS);
}