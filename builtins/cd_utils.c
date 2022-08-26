/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:56:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/26 14:15:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cd(t_env *env, char *key, char *to_old, int chek)
{
	char	*to_set;
	int		i;

	i = 0;
	if (chek || !ft_strcmp(key, "."))
	{
		to_set = getcwd(NULL, 1024);
		if (chek)
		{
			if (!to_set)
				to_set = ft_strdup(get_path("PWD", env));
			if (to_set)
				to_set = drari(i, to_set);
		}
		i = 1;
	}
	else
		to_set = get_path(key, env);
	if (chdir(to_set) == -1)
		chdirror(to_set);
	else
		env = update_path(env, to_set, to_old);
	if (i)
		free(to_set);
}

char	*get_path(char *key, t_env *env)
{
	t_env		*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->pair->key, key))
			return (tmp_env->pair->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	dup_path(t_env *tmp_env, char *to_set, char *to_up)
{
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->pair->key, to_up))
		{
			if (to_set)
			{
				if (tmp_env->pair->value)
					free(tmp_env->pair->value);
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
	return (env);
}
