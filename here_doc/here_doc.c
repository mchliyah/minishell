/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 19:01:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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
		if (!is_heredoc_next(cmd->content->indx, cmd->next))
		{
			ft_putstr_fd(str, (*data)->here_fd[indx][1]);
			ft_putstr_fd("\n", (*data)->here_fd[indx][1]);
		}
		free(str);
	}
	return (1);
}

void	exec_here_doc(t_list *tmp, t_data **data, int count)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	while (tmp)
	{
		if (!syntax_err_checker(tmp))
			exit(g_status);
		if (tmp->content->type == DELIMITER)
			here_doc(tmp, data);
		tmp = tmp->next;
	}
	close_here_doc_fd(data, count);
	while (i < count)
		free((*data)->here_fd[i++]);
	free((*data)->here_fd);
	exit (0);
}

void	allocat_heredoc(t_data **data, int count)
{
	int		i;

	i = 0;
	(*data)->here_fd = malloc(sizeof(int *) * count);
	while (i < count)
		(*data)->here_fd[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < count)
		pipe((*data)->here_fd[i++]);
}

int	get_here_doc(t_list *cmd, t_data **data)
{
	t_list	*tmp;
	int		pid;
	int		count;

	tmp = cmd;
	count = count_here(tmp);
	(*data)->here_size = count;
	pid = 1;
	if (count)
	{
		allocat_heredoc(data, count);
		pid = fork();
		if (pid == -1)
		{
			perror("fork():");
			exit (1);
		}
		if (!pid)
			exec_here_doc(tmp, data, count);
		else
			return (wait_heredoc(data, pid, count));
	}
	return (1);
}
