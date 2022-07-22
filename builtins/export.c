/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/22 11:55:55 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print(t_env *exp)
{
	while (export)
	{
		
	}
}

void	export_cmd(t_env *exp, t_list *c_line)
{
	if (!c_line->content->args[0])
	{
		print(exp);
		return (0);
	}
	else
	{
		while (exp->next)
			exp = export->next;
		exp->next = malloc(sizeof(t_env));
		exp->next->pair->key = ft_strdup(c_line->content->content);
		exp->next->pair->value = ft_strdup(c_line->content->args[0]);
	}
}
