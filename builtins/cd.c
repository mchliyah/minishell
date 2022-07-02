/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:19:19 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/02 20:45:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *path, t_env *env)
{
	t_env		*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!strncmp(tmp_env->value, path, ft_strlen(path)))
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

t_env	*update_path(t_env *tmp_env, char *path)
{
	char	*new;
	char	*up_path;

	new = ft_strjoin("PWD=", path);
	up_path = get_path("PWD=", tmp_env);
	up_path = ft_strdup(new);
	return (tmp_env);
}

t_env	*cd_cmd(t_list	*c_line, t_env *env)
{
	t_env	*tmp_env;
	char	*path;

	tmp_env = env;
	if (!c_line->content->args[0])
	{
		path = get_path("HOME=", env);
		if (chdir(path + 5) == -1)
			ft_putstr_fd("cd : argument error \n", 2);
		else
			tmp_env = update_path(tmp_env, path + 5);
	}
	else if (chdir(c_line->content->args[0]) == -1)
		ft_putstr_fd("cd : argument error \n", 2);
	else
		tmp_env = update_path(tmp_env, c_line->content->args[0]);
	return (tmp_env);
}
