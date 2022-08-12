/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:12:44 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 03:12:21 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//char	*expending(char *content, t_data *data)
//{
//	char	*saver;
//	char	*c;
//	int		i;
//
//	i = 0;
//	saver = ft_strdup("");
//	while (content[i])
//	{
////		if (content[i] == SINGLE_QUOTE)
////			c = single_quote(content, &i);
////	if (content[i] == '$')
////			c = double_quote(content, &i, data->env);
////		else
////		{
////			c = _string_getter(content, &i, data->env);
////			i--;
////		}
//		saver = _string_getter(content, &i, data->env);
//		saver = ft_strjoin(saver, c);
//		i++;
//	}
//	free(content);
//	return (saver);
//}
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
		if (!ft_strcmp(str, key_stop) && *str)
			break ;
		if (check_for_variables(str))
			str = _string_getter(str, 0, (*data)->env);
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
