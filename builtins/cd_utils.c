/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:56:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/18 18:23:33 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *key, t_env *env)
{
	t_env		*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!strcmp(tmp_env->pair->key, key))
			return (tmp_env->pair->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	dup_path(t_env *tmp_env, char *to_set, char *to_up)
{
	while (tmp_env)
	{
		if (!strcmp(tmp_env->pair->key, to_up))
		{
			if (to_set)
			{
				if (tmp_env->pair->value)
				// 	free(tmp_env->pair->value);
				tmp_env->pair->value = ft_strdup(to_set);
			}
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

t_env	*update_path(t_env *env, char *to_set, char	*to_old)
{
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = env;
	if (to_set)
	{
		while (to_set[i])
		{
			if (i != 0 && !to_set[i + 1] && to_set[i] == '/')
				to_set[i] = '\0';
			i++;
		}
	}
	dup_path(tmp_env, to_old, "OLDPWD");
	tmp_env = env;
	dup_path(tmp_env, to_set, "PWD");
	if(to_old)
		free(to_old);
	if (to_set)
		free(to_set);
	return (env);
}
