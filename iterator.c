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

	/*
	 *  left    output to 1   |_0_|_1_|
	 *  right input form 0 and output to 1 if there is no out redirection
	 */
void	execute_childes(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp, t_exec *exec)
{
	int	child;

	child = 0;
	exec->cmd_n++;
	if (this_pipe->left)
	{
		exec->cmd_n++;
		exec_cmd(this_pipe->left, env, exp, envp, child, exec);
		child = 1;
	}
	if (this_pipe->right)
	{
		exec->cmd_n++;
		exec_cmd(this_pipe->right, env, exp, envp, child, exec);
	}
}

/*
 * closing fds if pipe failed
 */
int	iterator(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp, t_exec *exec)
{
	if (this_pipe->left_p)
	{
//		exec->p_index += 2;
		iterator(this_pipe->left_p, env, exp, envp, exec);
	}
	execute_childes(this_pipe, env, exp, envp, exec);
	return (EXIT_SUCCESS);
}