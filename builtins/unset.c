/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 13:07:44 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_insid(t_env **env, t_env *prev, char **args, int i)
{
	t_env	*to_f;

	to_f = (*env)->next;
	while (env && to_f)
	{
		if (!ft_strncmp(to_f->pair->key, args[i], ft_strlen(to_f->pair->key)))
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
	while (args[i])
	{
		prev = *env;
		if (!ft_strncmp((*env)->pair->key, args[i]
				, ft_strlen((*env)->pair->key)))
		{
			*env = (*env)->next;
			free(prev->pair);
			free(prev);
		}
		else
			unset_insid(env, prev, args, i);
		i++;
	}
	free(args);
}
