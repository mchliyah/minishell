/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/04 03:36:05 by mchliyah         ###   ########.fr       */
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

t_env	*update_path(t_env *tmp_env, char *path)
{
	t_env	*tmp_env;
	char	*new;
	char	*up_path;

	return (tmp_env);
}

t_env	*cd_cmd(t_list	*c_line, t_env *env)
{
	char	*path;

	if (!c_line->content->args[0])
	{
		path = get_path("HOME", env);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd : argument error \n", 2);
			return (env);
		}
		env = update_path(env, path);
	}
	else if (chdir(c_line->content->args[0]) == -1)
		ft_putstr_fd("cd : argument error \n", 2);
	// else
	// 	env = update_path(env, c_line->content->args[0]);
	return (env);
}
