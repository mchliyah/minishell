/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:41:23 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/01 21:47:53 by mchliyah         ###   ########.fr       */
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

	i = 0;
	if (str[0] == '-')
		return (-1);
	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z')
		&& str[0] != '_' )
		return (-2);
	while (str[i])
	{
		if (str[i] == '-')
			return (-3);
		else
		{
			if (str[i] == '=' && str[i - 1] != '+')
				return (1);
			else if (str[i] == '=' && str[i - 1] == '+')
				return (2);
			else if (str[i] == '=')
				break ;
		}
		i++;
	}
	return (0);
}

int	exist(t_env *env, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		i--;
	while (env)
	{
		if (!strncmp(env->pair->key, arg, i))
			return (1);
		env = env->next;
	}
	return (0);
}
