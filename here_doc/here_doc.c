/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/05 17:50:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (!ft_strncmp(str, key_stop, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, tmpfile);
		free(str);
	}
	(*data)->p_in = open(TMP_FILE, O_RDONLY);
	if ((*data)->fd_in < 0)
	{
		unlink(TMP_FILE);
		perror("HEREDOC");
	}
}
