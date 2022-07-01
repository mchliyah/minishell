/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:42:24 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/01 14:13:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int env_init(t_pipe_line *pipeline, char **env)
{
	int		i;
	t_env	*my_env;
	t_env	*new;

    my_env = malloc(sizeof(t_env));
	if (!my_env)
		return (1);
	mv_env->value = ft_strdup(env[0]);
	env->next = NULL;
	pipeline->env = env;
	i = 1;
	while (env && env[0] && env[i])
	{
        new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}