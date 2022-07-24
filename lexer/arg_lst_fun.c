/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:53:40 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/24 12:53:41 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*list_new(char	*content)
{
	t_arg	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

t_arg	*list_last(t_arg *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	list_add_back(t_arg **lst, t_arg *new)
{
	if (!lst || !new)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		new->prev = list_last(*lst);
		(list_last(*lst))->next = new;
	}
}