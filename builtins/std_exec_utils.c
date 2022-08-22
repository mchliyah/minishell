/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:48:07 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/20 23:48:47 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env_char(t_env *env)
{
	t_env	*tmp;
	char	*fr;
	char	**arr;
	int		size;
	int		i;

	size = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * size + 1);
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->pair->key);
		fr = arr[i];
		arr[i] = ft_strjoin(arr[i], "=");
		free(fr);
		fr = arr[i];
		arr[i] = ft_strjoin(arr[i], tmp->pair->value);
		free(fr);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
