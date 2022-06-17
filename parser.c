/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/17 22:27:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_list	*priority(t_list	*listd_tokn, t_token *token)
{
	if (!listd_tokn)
		listd_tokn = ft_lstnew(token);
	else
		ft_lstadd_back(&listd_tokn, ft_lstnew(token));
	return (listd_tokn);
}
