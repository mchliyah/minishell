/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/18 21:22:17 by mchliyah         ###   ########.fr       */
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

void	dup_path(t_env *tmp_env, char *to_set, const char *to_up)
{
	while (tmp_env)
	{
		if (!strncmp(tmp_env->pair->key, to_up, ft_strlen(to_up)))
		{
			tmp_env->pair->value = strdup(to_set);
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
	dup_path(tmp_env, to_old, "OLDPWD=");
	tmp_env = env;
	dup_path(tmp_env, to_set, "PWD=");
	return (env);
}

void	exec_cd(t_env *env, char *key, char *to_old, int chek)
{
	char	*to_set;
	int		i;

	i = 0;
	if (chek)
	{
		to_set = strdup(get_path("PWD=", env));
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

	if (!c_line->content->args[0])
		exec_cd(env, "HOME=", get_path("PWD=", env), 0);
	else if (!strncmp(c_line->content->args[0], "-", 1))
		exec_cd(env, "OLDPWD=", get_path("PWD=", env), 0);
	else if (!strncmp(c_line->content->args[0], "..", 2))
		exec_cd(env, NULL, get_path("PWD=", env), 1);
	else if (!strncmp(c_line->content->args[0], ".", 1))
		return ;
	else
	{
		to_set = c_line->content->args[0];
		if (chdir(c_line->content->args[0]) == -1)
			ft_putstr_fd("cd: no such file or directory\n", 2);
		else
			env = update_path(env, to_set, get_path("PWD", env));
	}
	g_status = 0;
}
