/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:56:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/11 21:04:53 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *key, t_env *env)
{
	t_env		*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!strncmp(tmp_env->pair->key, key, ft_strlen(key)))
			return (tmp_env->pair->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	dup_path(t_env *tmp_env, char *to_set, char *to_up)
{
	while (tmp_env)
	{
		if (!strncmp(tmp_env->pair->key, to_up, ft_strlen(to_up)))
		{
			if (to_set)
				tmp_env->pair->value = ft_strdup(to_set);
			break ;
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
	return (env);
}
