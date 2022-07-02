/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/02 15:12:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_init(t_pipe_line *pipeline, char **env)
{
	int		i;
	t_env	*my_env;
	t_env	*new;

	my_env = malloc(sizeof(t_env));
	if (!my_env)
		return (0);
	my_env->value = ft_strdup(env[0]);
	my_env->next = 0;
	pipeline->env = my_env;
	i = 1;
	while (env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		my_env->next = new;
		my_env = new;
		i++;
	}
	return (1);
}

void	env_cmd(t_pipe_line *p_line)
{
	t_env	*env;

	env = p_line->env;
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}
