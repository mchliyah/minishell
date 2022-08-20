/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/20 21:53:19 by mchliyah         ###   ########.fr       */
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

bool	is_heredoc_next(int index, t_list *cmd)
{
	t_list	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->content->type == DELIMITER && cur->content->indx == index)
			return (true);
		cur = cur->next;
	}
	return (false);
}

int	here_doc(t_list *cmd, t_data **data)
{
	char	*str;
	int		indx;

	indx = cmd->content->indx;
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, cmd->next->content->content))
			break ;
		if (check_for_variables(str))
			str = h_string_getter(str, 0, (*data)->env);
		//close((*data)->here_fd[indx][0]);
		if (!is_heredoc_next(cmd->content->indx, cmd->next))
		{
			ft_putstr_fd(str, (*data)->here_fd[indx][1]);
			ft_putstr_fd("\n", (*data)->here_fd[indx][1]);
		//	close((*data)->here_fd[indx][1]);
		}
		free(str);
	}
	return (1);
}

int	get_here_doc(t_list *cmd, t_data **data)
{
	t_list	*tmp;
	int		pid;
	int		count;
	int		i;
	int		status;

	tmp = cmd;
	count = count_here(tmp);
	(*data)->here_size = count;
	i = 0;
	pid = 1;
	if (count)
	{
		(*data)->here_fd = malloc(sizeof(int *) * count);
		while (i < count)
			(*data)->here_fd[i++] = malloc(sizeof(int) * 2);
		i = 0;
		while (i < count)
			pipe((*data)->here_fd[i++]);
		pid = fork();
		if (pid == -1)
		{
			perror("fork():");
			exit (1);
		}
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			while (tmp)
			{
				if (!syntax_err_checker(tmp))
				{
					PV(g_status, "%d\n");
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
		else
		{
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
					i = 0;
					while (i < count)
					{
						close((*data)->here_fd[i][0]);
						close((*data)->here_fd[i][1]);
						i++;
					}
					kill(pid, SIGQUIT);
				}
				return (0);
			}
		}
	}
	return (1);
}
