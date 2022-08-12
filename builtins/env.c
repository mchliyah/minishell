/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 23:21:47 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*check_oldped(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (tmp)
	{
		if (!ft_strcmp(tmp->pair->key, "OLDPWD"))
			return (env);
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->next->pair->key, "OLDPWD"))
				return (env);
			tmp = tmp->next;
		}
		tmp->next = malloc(sizeof(t_env));
		tmp->next->pair = malloc(sizeof(t_pair));
		tmp->next->pair->key = ft_strdup("OLDPWD");
		tmp->next->pair->value = ft_strdup("");
		tmp->next->next = NULL;
	}
	return (env);
}

t_env	*get_env(char **envp)
{
	int		i;
	char	*tmp_value;
	t_env	*env;
	t_env	*my_env;
	t_env	*new;

	my_env = start(envp);
	if (!my_env)
		return (NULL);
	env = my_env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		tmp_value = ft_strdup(envp[i]);
		new->pair = init_pair(tmp_value);
		new->next = NULL;
		my_env->next = new;
		my_env = new;
		i++;
	}
	env = check_oldped(env);
	return (env);
}

void	env_cmd(t_env *env)
{
	if (!env)
		return ;
	if (!get_path("PATH", env))
	{
		ft_putstr_fd("bash: env: No such file or directory\n", 2);
		return ;
	}
	while (env)
	{
		if (env->pair->value && env->pair->value[0])
			printf("%s=%s\n", env->pair->key, env->pair->value);
		env = env->next;
	}
}
