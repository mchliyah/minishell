/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:36:48 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/23 19:50:01 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exp(char *str)
{
	int	i;
	int	len;
	int	join;

	i = 1;
	join = 0;
	if (str[0] == '-')
		return (-1);
	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z')
		&& str[0] != '_' )
		return (-2);
	len = ft_strlen(str);
	if (str[len - 1] == '+')
	{
		join = 1;
		len--;
	}
	while (i < len && str[i])
		if (!ft_isalnum(str[i++]))
			return (-3);
	if (join)
		return (1);
	return (0);
}

void	sort_exp(t_env **exp)
{
	t_env	*tmp;
	t_env	*tmp1;
	t_pair	*pair;

	if (*exp)
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

void	dup_at_end(t_env **tmpin, t_pair *to_exp)
{
	t_env	*tmp;

	tmp = *tmpin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->pair = malloc(sizeof(t_pair));
	if (tmp->next->pair)
	{
		tmp->next->pair->key = ft_strdup(to_exp->key);
		tmp->next->pair->value = NULL;
		if (to_exp->value)
			tmp->next->pair->value = ft_strdup(to_exp->value);
	}
	tmp->next->next = NULL;
}
