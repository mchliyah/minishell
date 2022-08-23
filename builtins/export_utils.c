/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:41:23 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/23 19:49:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	join_midle(t_env *tmp, t_pair *to_exp)
{
	char	*to_f;

	tmp = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->pair->key, to_exp->key))
		{
			if (tmp->pair->value)
			{
				to_f = tmp->pair->value;
				tmp->pair->value = ft_strjoin(tmp->pair->value, to_exp->value);
				free(to_f);
			}
			else
				tmp->pair->value = ft_strdup(to_exp->value);
			return (0);
		}
		tmp = tmp->next;
	}
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
	if (!join_midle(tmp, to_exp))
		return ;
	tmp = *tmp_in;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->pair = malloc(sizeof(t_pair));
	tmp->next->pair->key = ft_strdup(to_exp->key);
	tmp->next->pair->value = ft_strdup(to_exp->value);
	tmp->next->next = NULL;
}

t_env	*start_env(t_pair *to_exp)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->pair = malloc(sizeof(t_pair));
	ret->pair->key = ft_strdup(to_exp->key);
	ret->pair->value = NULL;
	if (to_exp->value)
		ret->pair->value = ft_strdup(to_exp->value);
	ret->next = NULL;
	return (ret);
}

t_env	**dup_not_exist_elem(t_env **env, t_pair *to_exp)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
		*env = start_env(to_exp);
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
