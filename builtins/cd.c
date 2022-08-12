/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 00:27:50 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

void	exec_cd(t_env *env, char *key, char *to_old, int chek)
{
	char	*to_set;
	int		i;

	i = 0;
	if (chek)
	{
		to_set = getcwd(NULL, 1024);
		if (to_set)
		{
			while (to_set[i])
				i++;
			while (i != 0 && to_set[i] != '/')
				i--;
			to_set[i + 1] = '\0';
		}
	}
	else
		to_set = get_path(key, env);
	if (chdir(to_set) == -1)
	{
		perror(to_set);
		g_status = 1;
	}
	else
		env = update_path(env, to_set, to_old);
	if (chek)
		free(to_set);
}

void	chdir_cd(t_env *env, char *to_set)
{
	if (chdir(to_set) == -1)
	{
		perror(to_set);
		g_status = 1;
	}
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

void	cd_cmd(t_list	*c_line, t_env *env)
{
	char	*to_set;

	to_set = NULL;
	if (c_line->content->arg)
		to_set = c_line->content->arg->content;
	if (!c_line->content->arg && !get_path("HOME", env))
	{
		printf("cd: HOME not set\n");
		g_status = 1;
		return ;
	}
	if (!c_line->content->arg
		|| !ft_strcmp(to_set, "~"))
		exec_cd(env, "HOME", getcwd(NULL, 1024), 0);
	else if (!ft_strcmp(to_set, "-"))
		exec_cd(env, "OLDPWD", getcwd(NULL, 1024), 0);
	else if (!ft_strcmp(to_set, ".."))
		exec_cd(env, NULL, getcwd(NULL, 1024), 1);
	else if (!ft_strcmp(to_set, "."))
		exec_cd(env, ".", getcwd(NULL, 1024), 1);
	else
		chdir_cd(env, to_set);
}
