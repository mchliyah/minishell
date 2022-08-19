/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:41:23 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 03:04:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_env	*tmp;

	tmp = *tmp_in;
	if (!*tmp_in)
	{
		(*tmp_in) = malloc(sizeof(t_env));
		(*tmp_in)->pair = malloc(sizeof(t_pair));
		(*tmp_in)->pair->key = ft_strdup(to_exp->key);
		(*tmp_in)->pair->value = ft_strdup(to_exp->value);
		(*tmp_in)->next = NULL;
		return ;
	}
	while (tmp)
	{
		if (!ft_strcmp(tmp->pair->key, to_exp->key))
		{
			if (tmp->pair->value)
				tmp->pair->value
					= ft_strjoin(tmp->pair->value, to_exp->value);
			else
				tmp->pair->value = ft_strdup(to_exp->value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *tmp_in;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->pair = malloc(sizeof(t_pair));
	tmp->next->pair->key = ft_strdup(to_exp->key);
	tmp->next->pair->value = ft_strdup(to_exp->value);
	tmp->next->next = NULL;
}

t_env	**dup_not_exist_elem(t_env **env, t_pair *to_exp)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
	{
		*env = malloc(sizeof(t_env));
		(*env)->pair = malloc(sizeof(t_pair));
		(*env)->pair->key = ft_strdup(to_exp->key);
		(*env)->pair->value = NULL;
		if (to_exp->value)
			(*env)->pair->value = ft_strdup(to_exp->value);
		(*env)->next = NULL;
	}
	else
	{
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
	return (env);
}

void	add_elem(t_env **env, t_pair *to_exp, int exist)
{
	t_env	*tmp;

	tmp = *env;
	if (!exist)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->pair->key, to_exp->key))
			{
				free(tmp->pair->value);
				tmp->pair->value = NULL;
				if (to_exp->value)
					tmp->pair->value = ft_strdup(to_exp->value);
				return ;
			}
			tmp = tmp->next;
		}
		env = dup_not_exist_elem(env, to_exp);
	}
	else
		dup_exist_elem(env, to_exp);
}
