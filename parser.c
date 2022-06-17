/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/17 00:43:14 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


t_list	*priority(t_list	*listd_tokn, t_token *token)
{
	if (!listd_tokn)
		ft_lstnew(token->content);
	else
	{
		if (token->type != REDIRECT_IN)
			ft_lstadd_back(&listd_tokn, ft_lstnew(token->content));
		else
			ft_lstadd_front(&listd_tokn, ft_lstnew(token->content));
	}
	return (listd_tokn);
}
