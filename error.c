/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:01:58 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/10 22:15:20 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int g_status;

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

void	exp_error(int ret, char *str)
{
	if (ret == -1)
	{
		write (2, "export : ", 10);
		write (2, &str, 2);
		write (2, "invalid option\n", 16);
	}
	else
	{
		ft_putstr_fd("export : ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	g_status = 1;
}
