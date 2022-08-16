/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/14 00:55:01 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_here_doc(t_list *cmd, t_data **data)
{
	t_list	*tmp;
	int		pid;

	tmp = cmd;
	pid = fork();
	if (pid == -1)
	{
		perror("fork():");
		exit (1);
	}
	if (!pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		while (tmp && tmp->next)
		{
			if (tmp->content->type == DELIMITER)
				if (!here_doc(tmp->next->content->content, data))
					exit (1);
			tmp = tmp->next;
		}
		exit (0);
	}
	return (1);
}

int	check_for_heredoc(t_p_line *pipe, t_data **data)
{
	if (pipe->left_p)
		check_for_heredoc(pipe->left_p, data);
	if (pipe->left)
		if (!get_here_doc(pipe->left, data))
			return (0);
	if (pipe->right)
		if (!get_here_doc(pipe->right, data))
			return (0);
	return (1);
}

int	here_doc(char *key_stop, t_data **data)
{
	int		tmpfile;
	char	*str;

	tmpfile = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmpfile < 0)
	{
		perror("HEREDOC");
		return (0);
	}
	while (1)
	{
		str = readline("heredoc> ");
		if (!str)
			printf("handle control D alm3lam\n");
		if (!ft_strcmp(str, key_stop))
			break ;
		if (check_for_variables(str))
			str = h_string_getter(str, 0, (*data)->env);
		ft_putstr_fd(str, tmpfile);
		ft_putstr_fd("\n", tmpfile);
		free(str);
	}
	(*data)->fd_in = open(TMP_FILE, O_RDONLY);
	if ((*data)->fd_in < 0)
	{
		unlink(TMP_FILE);
		perror("HEREDOC");
		return (0);
	}
	return (1);
}
