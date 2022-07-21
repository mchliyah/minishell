/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/20 22:39:54 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*unset_cmd(t_env *env, char **args)
{
	t_env	*prev;
	t_env	*to_f;
	int		i;

	prev = env;
	to_f = NULL;
	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(env->pair->key, args[i], ft_strlen(args[i])))
		{
			env = env->next;
			free(prev->pair);
			free(prev);
		}
		else
		{
			prev = env;
			to_f = env->next;
			while (env)
			{
				if (!ft_strncmp(to_f->pair->key, args[i], ft_strlen(args[i])))
				{
					prev->next = prev->next->next;
					free(to_f->pair);
					free(to_f);
					break ;
				}
				prev = prev->next;
				to_f = to_f->next;
			}
		}
		i++;
	}
	return (env);
}
