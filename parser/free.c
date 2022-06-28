/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/28 17:04:26 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lst(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (list)
	{
		free(list->content);
		list = list->next;
	}
	free(tmp);
}
