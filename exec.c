/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 21:46:18 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cmpair(char *content, char *key)
{
	if (!ft_strncmp(content, key, ft_strlen(content)))
		return (0);
	return (1);
}

void	open_pipe(t_data **exec)
{
	int	i;

	i = 0;
	if ((*exec)->cmd_i > 0)
	{
		if (dup2((*exec)->p_fd[(*exec)->p_in - 2], STDIN_FILENO) == -1)
		{
			printf("err and should take some work in dup2\n");
		}
	}
	if (((*exec)->cmd_i + 1 != (*exec)->pip_nb + 1))
	{
		if (dup2((*exec)->p_fd[(*exec)->p_in + 1], STDOUT_FILENO) == -1)
		{
			printf("err and should take some work in dup1\n");
		}
	}
	while (i < (*exec)->pip_nb * 2)
	{
		close((*exec)->p_fd[i]);
		i++;
	}
}

void	exec_cmd(t_list *cmd, char **envp, t_data **exec)
{
	char	*content;

	open_pipe(exec);
	content = cmd->content->content;
	if (!cmpair(content, "echo") || !cmpair(content, "ECHO"))
		echo(cmd);
	else if (!cmpair(content, "env") || !cmpair(content, "ENV"))
		env_cmd((*exec)->env);
	else if (!cmpair(content, "cd") || !cmpair(content, "CD"))
		cd_cmd(cmd, (*exec)->env);
	else if (!cmpair(content, "pwd") || !cmpair(content, "PWD"))
		pwd_cmd((*exec)->env);
	else if (!cmpair(content, "unset"))
	{
		unset_cmd(&(*exec)->env, cmd);
		unset_cmd(&(*exec)->exp, cmd);
	}
	else if (!cmpair(content, "export"))
		export_cmd(&(*exec)->exp, &(*exec)->env, cmd);
	else if (!cmpair(content, "exit"))
		(*exec)->exit = exit_cmd(cmd);
	else
		to_std((*exec)->env, envp, cmd);
}
