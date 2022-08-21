/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:46:19 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 10:46:20 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	close_here_fd(t_data **data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
		i++;
	}
}

int	parent_waiting(int pid, int count, t_data **data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (status > 255)
			g_status = 256 + WEXITSTATUS(status);
		else
			g_status = WEXITSTATUS(status);
		return (0);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_status = 1;
			close_here_fd(data, count);
			kill(pid, SIGQUIT);
		}
		return (0);
	}
	return (1);
}

void	here_doc_child(t_list *list, t_data **data)
{
	int		i;
	int		count;
	t_list	*tmp;

	tmp = list;
	count = (*data)->here_size;
	signal(SIGINT, SIG_DFL);
	while (tmp)
	{
		if (!syntax_err_checker(tmp))
		{
//			PV(g_status, "%d\n");
			exit(g_status);
		}
		if (tmp->content->type == DELIMITER)
			here_doc(tmp, data);
		tmp = tmp->next;
	}
	i = -1;
	while (++i < count)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
	}
	exit (0);
}

void	init_here_doc(t_data **data, int count)
{
	int	i;

	i = 0;
	(*data)->here_fd = malloc(sizeof(int *) * count);
	while (i < count)
		(*data)->here_fd[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < count)
		pipe((*data)->here_fd[i++]);
}
