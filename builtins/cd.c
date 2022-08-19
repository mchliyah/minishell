/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/19 15:24:04 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

void	chdirror(char *err)
{
	perror(err);
	g_status = 1;
}

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
			i = 1;
		}
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

void	chdir_cd(t_env *env, char *to_set)
{
	char	*tmp;

	tmp = NULL;
	if (chdir(to_set) == -1)
		chdirror(to_set);
	else
	{
		if (!strncmp("/", to_set, ft_strlen(to_set)))
			env = update_path(env, to_set, get_path("PWD", env));
		else
		{
			to_set = ft_strjoin("/", to_set);
			tmp = to_set;
			to_set = ft_strjoin(get_path("PWD", env), to_set);
			free(tmp);
			env = update_path(env, to_set, get_path("PWD", env));
			free(to_set);
		}
	}
}

void	cd_cmd(t_list	*c_line, t_env *env)
{
	char	*to_set;
	char	*cwd;

	to_set = NULL;
	g_status = 0;
	cwd = getcwd(NULL, 1024);
	if (c_line->content->arg)
		to_set = ft_strdup(c_line->content->arg->content);
	if (!c_line->content->arg && !get_path("HOME", env))
	{
		printf("cd: HOME not set\n");
		g_status = 1;
		return ;
	}
	if (!c_line->content->arg
		|| !ft_strcmp(to_set, "~"))
		exec_cd(env, "HOME", cwd, 0);
	else if (!ft_strcmp(to_set, "-"))
		exec_cd(env, "OLDPWD", cwd, 0);
	else if (!ft_strcmp(to_set, ".."))
		exec_cd(env, NULL, cwd, 1);
	else if (!ft_strcmp(to_set, "."))
		exec_cd(env, ".", cwd, 1);
	else
		chdir_cd(env, to_set);
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	if (to_set)
	{
		free(to_set);
		to_set = NULL;
	}
}
