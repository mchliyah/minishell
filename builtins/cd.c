/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/25 18:30:44 by mchliyah         ###   ########.fr       */
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
	while (to_set[i])
	{
		if (i != 0 && !to_set[i + 1] && to_set[i] == '/')
			to_set[i] = '\0';
		i++;
	}
	dup_path(tmp_env, to_old, "OLDPWD");
	tmp_env = env;
	dup_path(tmp_env, to_set, "PWD");
	return (env);
}

void	exec_cd(t_env *env, char *key, char *to_old, int chek)
{
	char	*to_set;
	int		i;

	i = 0;
	if (chek)
	{
		to_set = ft_strdup(get_path("PWD", env));
		while (to_set[i])
			i++;
		while (i != 0 && to_set[i] != '/')
			i--;
		to_set[i + 1] = '\0';
	}
	else
		to_set = get_path(key, env);
	if (chdir(to_set) == -1)
		ft_putstr_fd("cd: argument error \n", 2);
	else
		env = update_path(env, to_set, to_old);
	if (chek)
		free(to_set);
}

void	cd_cmd(t_list	*c_line, t_env *env)
{
	char	*to_set;

	if (!c_line->content->arg)
	{
		if (!get_path("HOME", env))
		{
			printf("cd: HOME not set\n");
			return ;
		}
		if (!c_line->content->arg
			|| !strncmp(c_line->content->arg->content, "~", 1))
			exec_cd(env, "HOME", get_path("PWD", env), 0);
	}
	else if (!strncmp(c_line->content->arg->content, "-", 1))
		exec_cd(env, "OLDPWD", get_path("PWD", env), 0);
	else if (!strncmp(c_line->content->arg->content, "..", 2))
		exec_cd(env, NULL, get_path("PWD", env), 1);
	else if (!strncmp(c_line->content->arg->content, ".", 1))
		return ;
	else
	{
		to_set = c_line->content->arg->content;
		if (chdir(c_line->content->arg->content) == -1)
			ft_putstr_fd("cd: no such file or directory\n", 2);
		else
		{
			if (!strncmp("/", to_set, ft_strlen(to_set)))
				env = update_path(env, to_set, get_path("PWD", env));
			else
			{
				to_set = ft_strjoin("/", to_set);
				to_set = ft_strjoin(get_path("PWD", env), to_set);
				env = update_path(env, to_set, get_path("PWD", env));
			}
		}
	}
	g_status = 0;
}
