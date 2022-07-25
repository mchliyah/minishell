/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/25 18:55:59 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*unset_cmd(t_env *env, t_list *cmd)
{
	t_env	*prev;
	t_env	*to_f;
	char	**args;
	int		i;

	prev = env;
	to_f = NULL;
	i = 1;
	args = arr_arg(cmd);
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
			while (env && to_f)
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
	free(args);
	return (env);
}
