/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/19 20:08:49 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*priority(t_list	*lst_token, t_token *token)
{
	if (!lst_token)
		lst_token = ft_lstnew(token);
	else
		ft_lstadd_back(&lst_token, ft_lstnew(token));
	return (lst_token);
}

void	add_childs_id(t_list *lst_token, int i)
{
	if (lst_token->content->type == PIPE)
	{
		lst_token->content->child = -1;
		lst_token = lst_token->next;
	}
	while (lst_token && lst_token->content->type != PIPE)
	{
		lst_token->content->child = i;
		lst_token = lst_token->next;
	}
}
// will return a parsed tree
t_list	*parse_to_tree(t_list *lst_token)
{
	int			i;
	t_fdinout	fds;

	i = 0;
	while (lst_token->next)
		lst_token = lst_token->next;
	while (lst_token->prev)
	{
		if (lst_token->content->type == PIPE)
			add_child(lst_token, i++);
		lst_token = lst_token->prev;
	}
	add_childs_id(lst_token, i);
	return (lst_token);
}
