/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/05 00:29:20 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	args_in(char *arg, t_pb *p)
{
	if (!ft_strncmp("here_doc", arg, 8))
	{
		p->here_doc = 1;
		return (6);
	}
	else
	{
		p->here_doc = 0;
		return (5);
	}
}

void	here_doc(char *key_stop, t_data **data)
{
	int		tmpfile;
	char	*str;

	tmpfile = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmpfile < 0)
		perror("HEREDOC");
	while (1)
	{
		str = readline("heredoc>");
		if (!ft_strcmp(str, key_stop, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, tmpfile);
		free(str);
	}
	data->p_in = open(TMP_FILE, O_RDONLY);
	if (p->fd_in < 0)
	{
		unlink(TMP_FILE);
		err_msg(ERR_HEREDOC);
	}
}
