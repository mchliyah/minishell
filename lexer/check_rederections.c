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

extern int	g_status;

bool	is_redirection(int this)
{
	if (this == REDIRECT_OUT_IN_APPEND_MD || this == REDIRECT_IN
		|| this == REDIRECT_OUT || this == DELIMITER
		|| this == LESSGREAT)
		return (true);
	return (false);
}

bool	is_not_next(t_list *it)
{
	if (!it->next || (it->next->content->type != WORD_CMD
			&& it->next->content->type != WORD
			&& it->next->content->type != REDIRECT_OUT
			&& it->next->content->type != REDIRECT_IN
			&& it->next->content->type != REDIRECT_OUT_IN_APPEND_MD))
		return (true);
	return (false);
}

void	syntax_err(void)
{
	g_status = 258;
	ft_putendl_fd("minishell: syntax error near unexpected token ", 2);
}


int	syntax_err_checker(t_list *token)
{
	t_list	*it;

	it = token;
	if (is_redirection(it->content->type))
	{
		if (!it->next || it->next->content->type != WORD)
		{
			if (it->next && it->next->content->type == SYNTAX_ERR)
			{
				g_status = 1;
				ft_putendl_fd("minishell: ambiguous redirect", 2);
				return (false);
			}
			syntax_err();
			return (false);
		}
	}
	else if (it->content->type == SYNTAX_ERR)
	{
		syntax_err();
		return (false);
	}
	else if (it->content->type == PIPE)
	{
		if (is_not_next(it))
		{
			syntax_err();
			return (false);
		}
	}
	return (true);
}

//int	check_gaven_file_rd(t_list *token)
//{
//	t_list	*it;
//
//	it = token;
//	while (it)
//	{
//		if (is_redirection(it->content->type))
//		{
//			if (!it->next || it->next->content->type != WORD)
//			{
//				if (it->next && it->next->content->type == SYNTAX_ERR)
//				{
//					g_status = 1;
//					ft_putendl_fd("minishell: ambiguous redirect", 2);
//					return (false);
//				}
//				syntax_err();
//				return (false);
//			}
//		}
//		else if (it->content->type == SYNTAX_ERR)
//		{
//			syntax_err();
//			return (false);
//		}
//		else if (it->content->type == PIPE)
//		{
//			if (is_not_next(it))
//			{
//				syntax_err();
//				return (false);
//			}
//		}
//		it = it->next;
//	}
//	return (true);
//}
