/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 01:41:09 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_insid(t_env **env, t_env *prev, char **args, int i)
{
	t_env	*to_f;

	to_f = NULL;
	if ((*env)->next)
		to_f = (*env)->next;
	while (env && to_f)
	{
		if (!ft_strcmp(to_f->pair->key, args[i]))
		{
			prev->next = prev->next->next;
			free(to_f->pair);
			free(to_f);
		}
		prev = prev->next;
		to_f = to_f->next;
	}
}

void	unset_cmd(t_env **env, t_list *cmd)
{
	t_env	*prev;
	char	**args;
	int		i;

	i = 1;
	args = arr_arg(cmd);
	if (env && *env)
	{	
		while (args[i])
		{
			prev = *env;
			if (!ft_strcmp((*env)->pair->key, args[i]))
			{
				*env = (*env)->next;
				free(prev->pair);
				free(prev);
			}
			else
				unset_insid(env, prev, args, i);
			i++;
		}
	}
	free(args);
}
