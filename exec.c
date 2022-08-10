/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/09 23:30:23 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int g_status;

int	cmpair(char *content, char *key)
{
	if (!ft_strncmp(content, key, ft_strlen(content)))
		return (0);
	return (1);
}

int	append_file(t_data **data, t_list *cmd, char *file)
{
	if (cmd->content->type == DELIMITER)
	{
		(*data)->fd_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if ((*data)->fd_out < 0)
			if (ft_putstr_fd("outfile Error", 2))
				return (0);
	}
	return (1);
}

void	open_files(t_data **data, t_list *cmd)
{
	t_list	*iterator;
	char	*file;

	iterator = cmd;
	while (iterator && iterator->next)
	{
		file = iterator->next->content->content;
		if (iterator->content->type == DELIMITER)
		{
			//PV(file, "%s\n");
			if (!here_doc(iterator->next->content->content, data))
				exit(g_status);
		}
		else if (iterator->content->type == REDIRECT_IN)
		{
			(*data)->fd_in = open(file, O_RDONLY);
			if ((*data)->fd_in < 0)
				if (ft_putstr_fd("infile Error", 2))
					exit(g_status);
		}
		else if (iterator->content->type == REDIRECT_OUT)
		{
			(*data)->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((*data)->fd_out < 0)
				if (ft_putstr_fd("outfile Error", 2))
					exit(g_status);
		}
		else if (!append_file(data, iterator, file))
			break ;
		iterator = iterator->next;
	}
}

void	open_pipe(t_data **data, t_list *cmd)
{
	int	i;

	i = 0;
	open_files(data, cmd);
//	if ((*data)->fd_in == -1 && (*data)->pip_nb > 0)
//	{
//		in = 0;
//		(*data)->fd_in = (*data)->p_fd[(*data)->p_in - 2];
//	}
//	if ((*data)->fd_out == -1 && (*data)->pip_nb > 0)
//	{
//		ou = 0;
//		(*data)->fd_out = (*data)->p_fd[(*data)->p_in + 1];
//	}
	if ((*data)->cmd_i > 0 || (*data)->fd_in != -1)
	{
		if ((*data)->fd_in == -1)
			(*data)->fd_in = (*data)->p_fd[(*data)->p_in - 2];
		if (dup2((*data)->fd_in, STDIN_FILENO) == -1)
			printf("err and should take some work in dup2\n");
	}
	if (((*data)->cmd_i + 1 != (*data)->pip_nb + 1) || (*data)->fd_out != -1)
	{
		if ((*data)->fd_out == -1)
			(*data)->fd_out = (*data)->p_fd[(*data)->p_in + 1];
		if (dup2((*data)->fd_out, STDOUT_FILENO) == -1)
			printf("err and should take some work in dup1\n");
	}
	while (i < (*data)->pip_nb * 2)
	{
		close((*data)->p_fd[i]);
		i++;
	}
}

void	exec_cmd(t_list *in_cmd, t_data **data)
{
	t_list	*cmd;
	int		f_pid;
	char	*content;

	f_pid = 0;
	if ((*data)->pip_nb != 0)
		f_pid = fork();
	if (f_pid == -1)
	{
		perror("fork(): ");
		exit(g_status);
	}
	if (f_pid == 0)
	{
		open_pipe(data, in_cmd);
		while (in_cmd->content->type != WORD_CMD)
			in_cmd = in_cmd->next;
		cmd = in_cmd;
		content = cmd->content->content;
		if (!cmpair(content, "echo") || !cmpair(content, "ECHO"))
			echo(cmd);
		else if (!cmpair(content, "env") || !cmpair(content, "ENV"))
			env_cmd((*data)->env);
		else if (!cmpair(content, "cd") || !cmpair(content, "CD"))
			cd_cmd(cmd, (*data)->env);
		else if (!cmpair(content, "pwd") || !cmpair(content, "PWD"))
			pwd_cmd((*data)->env);
		else if (!cmpair(content, "unset"))
		{
			unset_cmd(&(*data)->env, cmd);
			unset_cmd(&(*data)->exp, cmd);
		}
		else if (!cmpair(content, "export"))
			export_cmd(&(*data)->exp, &(*data)->env, cmd);
		else if (!cmpair(content, "exit"))
			(*data)->exit = exit_cmd(cmd);
		else
			to_std((*data)->env, cmd, data);
		if ((*data)->pip_nb != 0)
			exit(g_status);
	}
}
