/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 19:47:17 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_status;

void	del_or_redrction(t_data **data, t_list *iterator, char *file)
{
	if (iterator->content->type == REDIRECT_IN
		|| iterator->content->type == DELIMITER)
		redirect_ins(file, iterator, data);
	else if (iterator->content->type == REDIRECT_OUT
		|| iterator->content->type == LESSGREAT)
	{
		if (iterator->content->type == LESSGREAT)
		{
			(*data)->fd_in = open(file, O_RDWR | O_CREAT, 0644);
			if ((*data)->fd_in < 0)
				fd_error_exit("open");
		}
		else
		{
			(*data)->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((*data)->fd_out < 0)
				fd_error_exit("open");
		}
	}
}

bool	open_files(t_data **data, t_list *cmd)
{
	t_list	*iterator;
	char	*file;

	iterator = cmd;
	while (iterator)
	{
		if (iterator->next)
		{
			file = iterator->next->content->content;
			del_or_redrction(data, iterator, file);
		}
		else if (iterator->content->type == WORD
			&& iterator->prev->content->type != DELIMITER
			&& iterator->prev->content->type != REDIRECT_IN
			&& iterator->prev->content->type != REDIRECT_OUT_IN_APPEND_MD
			&& iterator->prev->content->type != LESSGREAT
			&& iterator->prev->content->type != REDIRECT_OUT)
			(*data)->fd_in = open(iterator->content->content, O_RDONLY);
		if (!append_file(data, iterator, file))
			return (false);
		iterator = iterator->next;
	}
	return (true);
}

bool	open_pipe(t_data **data, t_list *cmd)
{
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
	}
	ft_close_fd(data);
	return (true);
}

bool	ft_exec_child(t_list *cmd, t_data **data, t_list *in_cmd)
{
	char	*content;

	signal(SIGQUIT, SIG_DFL);
	if (!open_pipe(data, in_cmd))
		return (false);
	if (cmd->content->type != WORD_CMD)
		exit(1);
	while (in_cmd->content->type != WORD_CMD)
		in_cmd = in_cmd->next;
	content = in_cmd->content->content;
	if (is_builtins(content))
		buuiltins(content, in_cmd, data);
	else
		to_std(in_cmd, data);
	if ((*data)->pip_nb != 0)
		exit(1);
	return (true);
}

bool	exec_cmd(t_list *in_cmd, t_data **data)
{
	t_list	*cmd;
	int		f_pid;

	f_pid = 0;
	cmd = in_cmd;
	while (cmd->content->type != WORD_CMD && cmd->next)
		cmd = cmd->next;
	if ((*data)->pip_nb != 0 || !is_builtins(cmd->content->content))
		f_pid = fork();
	if (f_pid == -1)
	{
		perror("fork(): ");
		exit (1);
	}
	if (f_pid == 0)
	{
		if (!ft_exec_child(cmd, data, in_cmd))
			return (false);
	}
	return (true);
}
