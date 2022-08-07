/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rederections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:26:39 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/06 18:26:42 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


bool	is_redirection(int this)
{
	if (this == REDIRECT_OUT_IN_APPEND_MD || this == REDIRECT_IN
		|| this == REDIRECT_OUT || this == DELIMITER)
		return (true);
	return (false);
}

/*
 *  this fun for checking is the user gave the file with redirections
 *  and also unclosed pipe by cmd
   !! if the check_gaven_file_rd returns false I should free the allocated mem
 */
int	check_gaven_file_rd(t_list *token)
{
	t_list	*it;

	it = token;
	while (it)
	{
		if (is_redirection(it->content->type))
		{
			if (!it->next || it->next->content->type != WORD)
			{
				g_status = 258;
				ft_putendl_fd("minishell: syntax error near unexpected token ", 2);
				return (false);
			}
		}
		else if (it->content->type == SYNTAX_ERR)
		{
			g_status = 258;
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			return (false);
		}
		else if (it->content->type == EPIPE)
		{
			if (!it->next || (it->next->content->type != WORD_CMD
					&& it->next->content->type != WORD
					&& it->next->content->type != REDIRECT_OUT
					&& it->next->content->type != REDIRECT_IN
					&& it->next->content->type != REDIRECT_OUT_IN_APPEND_MD))
			{
				g_status = 258;
				ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
				return (false);
			}
		}
		it = it->next;
	}
	return (true);
}
