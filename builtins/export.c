/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 12:30:03 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_exp(t_env **exp)
{
	t_env	*tmp;
	t_env	*tmp1;
	t_pair	*pair;

	if (exp)
	{
		tmp = *exp;
		while (tmp->next)
		{
			tmp1 = tmp->next;
			while (tmp1)
			{
				if (ft_strcmp(tmp->pair->key, tmp1->pair->key) > 0)
				{
					pair = tmp->pair;
					tmp->pair = tmp1->pair;
					tmp1->pair = pair;
				}
				tmp1 = tmp1->next;
			}
			tmp = tmp->next;
		}
	}
}

static void	print(t_env *exp)
{
	while (exp)
	{
		printf("declare -x %s=\"%s\"\n", exp->pair->key, exp->pair->value);
		exp = exp->next;
	}
}

void	export_cmd(t_env **exp, t_list *c_line)
{
	char	**args;

	if (!c_line->content->arg)
	{
		print(*exp);
		return ;
	}
	else
	{
		while ((*exp)->next)
			*exp = (*exp)->next;
		(*exp)->next = malloc(sizeof(t_env));
		(*exp)->next->pair = malloc(sizeof(t_pair));
		args = ft_split(c_line->content->arg->content, '=');
		(*exp)->next->pair->key = ft_strdup(args[0]);
		(*exp)->next->pair->value = ft_strdup(args[1]);
		(*exp)->next->next = NULL;
	}
}
