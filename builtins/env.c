/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/04 21:41:47 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (env);
}

void	env_cmd(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=%s\n", env->pair->key, env->pair->value);
		env = env->next;
	}
}
