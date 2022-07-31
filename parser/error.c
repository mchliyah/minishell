/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:01:58 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/31 14:53:15 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(t_list *lst_token, t_token *token)
{
	printf("%s : SYNTAX ERROR !\n", token->content);
	free_lst(lst_token);
}

void	error_check(t_list *lst_token)
{
	t_list	*check;

	check = lst_token;
	while (check)
	{
		if (check->content->type == SYNTAX_ERR)
			error_exit(lst_token, check->content);
		check = check->next;
	}
}
