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

//int	open_files(t_data **data, t_list *cmd)
//	{
//		while (cmd->content.)
//		{
//
//		}
////}

void	open_pipe(t_data **data, t_list *cmd)
{
	int	i;

	i = 0;
//	open_files(data, cmd);
	if ((*data)->cmd_i > 0)
	{
		if (dup2((*data)->p_fd[(*data)->p_in - 2], STDIN_FILENO) == -1)
		{
			printf("err and should take some work in dup2\n");
		}
	}
	if (((*data)->cmd_i + 1 != (*data)->pip_nb + 1))
	{
		if (dup2((*data)->p_fd[(*data)->p_in + 1], STDOUT_FILENO) == -1)
		{
			printf("err and should take some work in dup1\n");
		}
	}
	while (i < (*data)->pip_nb * 2)
	{
		close((*data)->p_fd[i]);
		i++;
	}
}

void	exec_cmd(t_list *cmd, char **envp, t_data **data)
{
	int		f_pid;
	char	*content;

	f_pid = fork();
	if (f_pid == -1)
	{
		perror("fork(): ");
		exit(1);
	}
	if (f_pid == 0)
	{
		open_pipe(data, cmd);
		content = cmd->content->content;
		if (!cmpair(content, "echo") || !cmpair(content, "ECHO"))
			echo(cmd);
		else if (!cmpair(content, "env") || !cmpair(content, "ENV"))
			env_cmd((*data)->env);
		else if (!cmpair(content, "cd") || !cmpair(content, "CD"))
			cd_cmd(cmd, (*data)->env);
		else if (!cmpair(content, "pwd") || !cmpair(content, "PWD"))
			pwd_cmd((*data)->env);
		else if (!cmpair(content, "unset")) {
			unset_cmd(&(*data)->env, cmd);
			unset_cmd(&(*data)->exp, cmd);
		}
		else if (!cmpair(content, "export"))
			export_cmd(&(*data)->exp, &(*data)->env, cmd);
		else if (!cmpair(content, "exit"))
			(*data)->exit = exit_cmd(cmd);
		else
			to_std((*data)->env, envp, cmd);
		exit(g_status);
	}
}
