/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:25:12 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 13:25:15 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_out_redection_next(t_list *it)
{
	t_list	*tmp;

	tmp = it;
	while (tmp)
	{
		if (tmp->content->type == REDIRECT_OUT
			|| tmp->content->type == REDIRECT_OUT_IN_APPEND_MD)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_close_fd(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->here_size)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < (*data)->pip_nb * 2)
		close((*data)->p_fd[i++]);
	close((*data)->fd_out);
}

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

void	fd_error_exit(char *str)
{
	perror(str);
	exit(127);
}

void	redirect_ins(char *file, t_list *iterator, t_data **data)
{
	if (iterator->content->type == DELIMITER)
	{
		(*data)->fd_in = (*data)->here_fd[iterator->content->indx][0];
		if ((*data)->fd_in < 0)
			fd_error_exit("open");
	}
	else
		(*data)->fd_in = open(file, O_RDONLY);
	if ((*data)->fd_in < 0)
		fd_error_exit("open");
}
