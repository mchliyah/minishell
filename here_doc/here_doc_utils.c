/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:45:56 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/26 14:34:44 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	count_here(t_list *list)
{
	int		counter;
	t_list	*lst;

	counter = 0;
	lst = list;
	while (lst)
	{
		if (lst->content->type == DELIMITER && lst->content->indx != -1)
			counter = lst->content->indx + 1;
		lst = lst->next;
	}
	return (counter);
}

void	close_here_doc_fd(t_data **data, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
	}
}

// int	free_fds_here(t_data **data, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 		free((*data)->here_fd[i++]);
// 	free((*data)->here_fd);
// 	return (0);
// }

int	wait_heredoc(t_data **data, int pid, int count)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (status > 255)
		{
			g_status = 256 + WEXITSTATUS(status);
			return (0);
		}
		else
			g_status = WEXITSTATUS(status);
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_status = 1;
			close_here_doc_fd(data, count);
			kill(pid, SIGQUIT);
		}
		return (0);
	}
	return (1);
}

int	index_heredoc(t_data **data)
{
	int		max;
	t_list	*list;
	int		indx;
	int		there;

	indx = 0;
	there = 0;
	max = 0;
	list = (*data)->lst_tok;
	while (list)
	{
		if (list->content->type == DELIMITER)
		{
			max++;
			list->content->indx = indx;
			there = 1;
		}
		else if (list->content->type == PIPE && there)
		{
			indx++;
			there = 0;
		}
		list = list->next;
	}
	return (max);
}
