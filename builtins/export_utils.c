/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:41:23 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/01 23:15:29 by mchliyah         ###   ########.fr       */
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

int	elem_exist(t_env *env, char *arg)
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

void	dup_exist_elem(t_env *tmp, char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (str[i] != '=')
		i++;
	j = ++i;
	while (str[j])
		j++;
	if (i != j)
		value = env_dup(str, j, i);
	while (tmp)
	{
		if (!strncmp(tmp->pair->key, &str[0], ft_strlen(tmp->pair->key)))
			tmp->pair->value = ft_strjoin(tmp->pair->value, value);
		tmp = tmp->next;
	}
	free(value);
}

t_env	*dup_not_exist_elem(t_env *tmp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		tmp->pair->key = env_dup(str, i - 1, j);
	else
		tmp->pair->key = env_dup(str, i, j);
	j = ++i;
	while (str[i])
		i++;
	if (i != j)
		tmp->pair->value = env_dup(str, i, j);
	else
		tmp->pair->value = NULL;
	return (tmp);
}
