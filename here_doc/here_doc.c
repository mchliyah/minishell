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

	tmp = cmd;
	count = count_here(tmp);
	(*data)->here_size = count;
	if (count)
	{
		init_here_doc(data, count);
		pid = fork();
		if (pid == -1)
		{
			perror("fork():");
			exit (1);
		}
		if (!pid)
		{
			here_doc_child(cmd, data);
		}
		else
			if (!parent_waiting(pid, count, data))
				return (0);
	}
	return (1);
}
