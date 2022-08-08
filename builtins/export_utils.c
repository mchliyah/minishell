/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:41:23 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/08 01:06:38 by mchliyah         ###   ########.fr       */
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

void	dup_exist_elem(t_env **tmp_in, t_pair *to_exp)
{
	t_env	**tmp;

	tmp = tmp_in;
			HERE;
	while (*tmp)
	{
		if (!strncmp((*tmp)->pair->key, to_exp->key,
				ft_strlen((*tmp)->pair->key)))
		{
			HERE;
			if ((*tmp)->pair->value)
				(*tmp)->pair->value
					= ft_strjoin((*tmp)->pair->value, to_exp->value);
			else
				(*tmp)->pair->value = ft_strdup(to_exp->value);
			return ;
		}
			HERE;
		(*tmp) = (*tmp)->next;
	}
	*tmp = malloc(sizeof(t_env));
	(*tmp)->pair = malloc(sizeof(t_pair));
	(*tmp)->pair->key = ft_strdup(to_exp->key);
	(*tmp)->pair->value = ft_strdup(to_exp->value);
	(*tmp)->next = NULL;
}

t_env	*dup_not_exist_elem(t_pair *to_exp)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->pair = malloc(sizeof(t_pair));
			HERE;
	if (ret->pair)
	{
		ret->pair->key = ft_strdup(to_exp->key);
		ret->pair->value = NULL;
		if (to_exp->value)
			ret->pair->value = ft_strdup(to_exp->value);
	}
			HERE;
	return (ret);
}
