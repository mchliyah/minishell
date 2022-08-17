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
	else
		wait(NULL);
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
		str = readline("> ");
		if (!str || !ft_strcmp(str, key_stop))
			break ;
		if (check_for_variables(str))
			str = h_string_getter(str, 0, (*data)->env);
		ft_putstr_fd(str, tmpfile);
		ft_putstr_fd("\n", tmpfile);
		free(str);
	}
	return (1);
}
