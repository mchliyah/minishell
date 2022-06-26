/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:01:58 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/26 20:12:00 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	error_exit(t_list *lst_token)
{
	printf("SYNTAX ERROR\n");
	free_lst(lst_token);
	exit(0);
}

void	error_check(t_list *lst_token)
{
	t_list	*check;

	check = lst_token;
	while (check)
	{
		if (check->content->type == SYNTAX_ERR)
			error_exit(lst_token);
		check = check->next;
	}
}
