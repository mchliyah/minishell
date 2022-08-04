/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/04 20:58:01 by mchliyah         ###   ########.fr       */
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
//	char buff[100];
//	int rd;
	int	i;
	int	f_pid;
	int	_f_pid;

	if (this_pipe->left)
	{
		f_pid = fork();
		if (f_pid == -1)
		{
			perror("fork(): ");
			exit(1);
		}
		if (f_pid == 0)
		{
			PV(exec->cmd_i, "--cmd in %d\n");
			exec_cmd(this_pipe->left, envp, exec);
			exit(g_status);
		}
		(*exec)->cmd_i++;
	}
	(*exec)->p_in += 2;
	if (this_pipe->right)
	{
		_f_pid = fork();
		if (_f_pid == -1)
		{
			perror("fork(): ");
			exit(1);
		}
		if (_f_pid == 0)
		{
//			rd = read(exec->p_fd[0], buff, 100);
//			buff[rd] = '\0';
//			write (2, buff, ft_strlen(buff));
//			exit (0);
			PV(exec->cmd_i, "cmd in %d\n");
			exec_cmd(this_pipe->right, envp, exec);
			exit(g_status);
		}
		(*exec)->cmd_i++;
	}
//	while (wait(0) > 0)
//		;
	//return (1);
}

/*
 * closing fds if pipe failed
 */
int	iterator(t_pipe_line *this_pipe, char **envp, t_data **exec)
{
	int	j;

	if (this_pipe->left_p)
	{
		iterator(this_pipe->left_p, envp, exec);
	}
	execute_childes(this_pipe, envp, exec);
	PV((*exec)->exit, "%d\n");
	return (EXIT_SUCCESS);
}
