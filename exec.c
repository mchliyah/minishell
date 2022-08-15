/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/11 23:20:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int g_status;

int	append_file(t_data **data, t_list *cmd, char *file)
{
	if (cmd->content->type == REDIRECT_OUT_IN_APPEND_MD)
	{
		(*data)->fd_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if ((*data)->fd_out < 0)
			if (ft_putstr_fd("outfile Error", 2))
				return (0);
	}
	return (1);
}

bool	open_files(t_data **data, t_list *cmd)
{
	t_list	*iterator;
	char	*file;

	iterator = cmd;
	while (iterator)
	{
		if (iterator->next)
			file = iterator->next->content->content;
		if (iterator->content->type == REDIRECT_IN || iterator->content->type == WORD)
		{
			PV(file, "|%s|\n");
			(*data)->fd_in = open(file, O_RDONLY);
			if ((*data)->fd_in < 0)
				if (ft_putstr_fd("minishell: NO such file or directory\n", 2))
					return (false);
		}
		else if (iterator->content->type == REDIRECT_OUT
			|| iterator->content->type == LESSGREAT)
		{
			(*data)->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((*data)->fd_out < 0)
				if (ft_putstr_fd("minishell: NO such file or directory\n", 2))
					return (false);
		}
		else if (!append_file(data, iterator, file))
			return (false);
		iterator = iterator->next;
	}
	return (true);
}

bool	open_pipe(t_data **data, t_list *cmd)
{
	int	i;

	i = 0;
	if (!open_files(data, cmd))
		return (false);
	if ((*data)->cmd_i > 0 || (*data)->fd_in != -1)
	{
		if ((*data)->fd_in == -1)
			(*data)->fd_in = (*data)->p_fd[(*data)->p_in - 2];
		if (dup2((*data)->fd_in, STDIN_FILENO) == -1)
		{
			printf("error dup2 failed to duplicate fd\n");
			return (false);
		}
		close((*data)->fd_in);
	}
	if (((*data)->cmd_i + 1 != (*data)->pip_nb + 1) || (*data)->fd_out != -1)
	{
		if ((*data)->fd_out == -1)
			(*data)->fd_out = (*data)->p_fd[(*data)->p_in + 1];
		if (dup2((*data)->fd_out, STDOUT_FILENO) == -1)
			if (ft_putstr_fd("error dup2 failed to duplicate fd\n", 2))
				return (false);
		close((*data)->fd_out);
	}
	while (i < (*data)->pip_nb * 2)
		close((*data)->p_fd[i++]);
	return (true);
}

bool	exec_cmd(t_list *in_cmd, t_data **data)
{
	t_list	*cmd;
	int		f_pid;
	char	*content;

	f_pid = 0;
	cmd = in_cmd;
	while (cmd->content->type != WORD_CMD)
		cmd = cmd->next;
	if ((*data)->pip_nb != 0 || !is_builtins(cmd->content->content))
		f_pid = fork();
	if (f_pid == -1)
	{
		perror("fork(): ");
		(*data)->exit = 1;
		return (false);
	}
	if (f_pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (!open_pipe(data, in_cmd))
			return (false);
		while (in_cmd->content->type != WORD_CMD)
			in_cmd = in_cmd->next;
		content = in_cmd->content->content;
		if (is_builtins(content))
			buuiltins(content, in_cmd, data);
		else
			to_std(in_cmd, data);
	}
	return (true);
}
