/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:09:58 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/23 18:18:50 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*prev_env;

	while (env)
	{
		prev_env = env;
		env = env->next;
		free(prev_env->pair->key);
		if (prev_env->pair->value)
			free(prev_env->pair->value);
		free(prev_env->pair);
		free(prev_env);
	}
}

void	free_data(t_data *data)
{
	free_env(data->env);
	free_env(data->exp);
	free(data);
}
