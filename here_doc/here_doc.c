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

	tmp = cmd;
	while (tmp && tmp->next)
	{
		if (tmp->content->type == DELIMITER)
			if (!here_doc(tmp->next->content->content, data))
				return (0);
		tmp = tmp->next;
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
		if (!str)

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
