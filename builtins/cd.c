/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/04 20:33:27 by mchliyah         ###   ########.fr       */
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

t_env	*update_path(t_env *env, char *to_set, char	*to_old)
{
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = env;
	while (to_set[i])
	{
		if (i != 0 && !to_set[i + 1] && to_set[i] == '/')
			to_set[i] = '\0';
		i++;
	}
	while (tmp_env)
	{
		if (!strncmp(tmp_env->pair->key, "OLDPWD", ft_strlen("OLDPWD")))
		{
			tmp_env->pair->value = strdup(to_old);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	tmp_env = env;
	while (tmp_env)
	{
		if (!strncmp(tmp_env->pair->key, "PWD", ft_strlen("PWD")))
		{
			tmp_env->pair->value = strdup(to_set);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	return (env);
}

void	cd_cmd(t_list	*c_line, t_env *env)
{
	char	*to_set;
	char	*to_old;
	int		i;

	i = 0;
	to_old = get_path("PWD", env);
	if (!c_line->content->args[0])
	{
		to_set = get_path("HOME", env);
		if (chdir(to_set) == -1)
			ft_putstr_fd("cd: argument error \n", 2);
		else
			env = update_path(env, to_set, to_old);
	}
	else if (!strncmp(c_line->content->args[0], "-", 1))
	{
		to_set = get_path("OLDPWD", env);
		if (chdir(to_set) == -1)
			ft_putstr_fd("cd: argument error \n", 2);
		else
			env = update_path(env, to_set, to_old);
	}
	else if (!strncmp(c_line->content->args[0], "..", 2))
	{
		to_set = strdup(to_old);
		while (to_set[i])
			i++;
		while (i != 0 && to_set[i] != '/')
			i--;
		to_set[i + 1] = '\0';
		if (chdir(to_set) == -1)
			ft_putstr_fd("cd: argument error \n", 2);
		else
			env = update_path(env, to_set, to_old);
		free(to_set);
	}
	else if (!strncmp(c_line->content->args[0], ".", 1))
		return ;
	else
	{
		to_set = c_line->content->args[0];
		if (chdir(c_line->content->args[0]) == -1)
			ft_putstr_fd("cd: no such file or directory\n", 2);
		else
			env = update_path(env, to_set, to_old);
	}
	// else
	// env = update_path(env, path);
}
