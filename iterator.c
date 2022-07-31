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
void	execute_childes(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp, t_exec *exec)
{
	int	child;

	child = 0;
	printf("____________p_index %d\n", exec->p_index);
	if (this_pipe->left)
	{
		printf("l---------%s----------\n", this_pipe->left->content->content);
		printf("cmd_n=>%d\n", exec->cmd_n);
		exec_cmd(this_pipe->left, env, exp, envp, child, exec);
		exec->cmd_n++;
		child = 1;
	}
	exec->p_index += 2;
	if (this_pipe->right)
	{
		printf("r---------%s----------\n", this_pipe->right->content->content);
		printf("cmd_n =>%d\n", exec->cmd_n);
		exec_cmd(this_pipe->right, env, exp, envp, child, exec);
		exec->cmd_n++;
	}
}

/*
 * closing fds if pipe failed
 */
int	iterator(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp, t_exec *exec)
{
	int i;
	int j;
	if (this_pipe->left_p)
	{
		iterator(this_pipe->left_p, env, exp, envp, exec);
	}
	exec->p_index += 2;
	execute_childes(this_pipe, env, exp, envp, exec);
	i = 0;
	j = ((exec->cmd_size - 1) * 2);
	while (i < j)
	{
	//	printf("i\n");
		close(exec->p_fd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}