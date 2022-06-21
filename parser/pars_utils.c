/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:49:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/22 00:35:04 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*linked_token(t_list	*lst_token, t_token *token)
{
	if (!lst_token)
		lst_token = ft_lstnew(token);
	else
		ft_lstadd_back(&lst_token, ft_lstnew(token));
	return (lst_token);
}

int	pipe_exist(t_list *lst)
{
	while (lst)
	{
		if (lst->content->type == PIPE)
			return (1);
		lst = lst->next;
	}
	return (0);
}

