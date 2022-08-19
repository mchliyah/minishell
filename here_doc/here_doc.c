/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/19 03:39:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_putstr_fd(str, (*data)->here_fd[indx][1]);
		ft_putstr_fd("\n", (*data)->here_fd[indx][1]);
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

	tmp = cmd;
	count = count_here(tmp);
	i = 0;
	if (count)
	{
		(*data)->here_fd = malloc(sizeof(int *) * count);
		while (i < count)
			(*data)->here_fd[i++] = malloc(sizeof(int) * 2);
		i = 0;
		while (i < count)
			pipe((*data)->here_fd[i++]);
	}
	tmp = cmd;
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
			if (tmp->content->type == DELIMITER)
				if (!here_doc(tmp, data))
					exit (1);
			tmp = tmp->next;
		}
		while (i < count)
			close((*data)->here_fd[i++][1]);
		exit (0);
	}
	else
		wait(NULL);
	i = 0;
	return (1);
}

// char	*get_pipe_fd(char *key, t_data *data, t_p_line *pipe)
// {
// 	int	*here_fd;

// 	here_fd = malloc(count_here(pipe) * 2);
// }
