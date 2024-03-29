/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 00:26:36 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 18:53:47 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	shelvl(t_env **env)
{
	t_env	*tmp_env;
	int		to_set;
	char	*itoa_val;

	tmp_env = *env;
	itoa_val = NULL;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->pair->key, "SHLVL"))
		{
			to_set = ft_atoi(tmp_env->pair->value);
			free(tmp_env->pair->value);
			itoa_val = ft_itoa(to_set + 1);
			tmp_env->pair->value = ft_strdup(itoa_val);
			free(itoa_val);
		}
		tmp_env = tmp_env->next;
	}
}

int	init_pipes(t_data **data)
{
	int			i;

	(*data)->cmd_i = 0;
	(*data)->p_in = 0;
	(*data)->exit = 0;
	(*data)->p_fd = NULL;
	(*data)->fd_in = -1;
	(*data)->fd_out = -1;
	if ((*data)->pip_nb != 0)
	{
		(*data)->p_fd = malloc((2 * (*data)->pip_nb) * sizeof(int ));
		i = 0;
		while (i < (*data)->pip_nb)
		{
			if (pipe((*data)->p_fd + i * 2) < 0)
			{
				perror("pipe()");
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

t_env	*start(char **envp)
{
	t_env	*my_env;
	char	*tmp_value;

	my_env = malloc(sizeof(t_env));
	if (!my_env)
		return (NULL);
	tmp_value = ft_strdup(envp[0]);
	my_env->pair = init_pair(tmp_value);
	if (!my_env->pair)
		return (NULL);
	my_env->next = NULL;
	return (my_env);
}
