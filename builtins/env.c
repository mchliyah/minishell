/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/05 19:02:29 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_dup(char *tmp_val, int i, int j)
{
	char	*dup;
	int		k;

	k = 0;
	dup = malloc(sizeof(char) * (i - j + 1));
	if (!dup)
		return (NULL);
	while (j < i)
	{
		dup[k++] = tmp_val[j];
		j++;
	}
	dup[k] = '\0';
	return (dup);
}

t_pair	*init_pair(char *tmp_val)
{
	t_pair	*pair;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pair = malloc(sizeof(t_pair));
	if (!pair)
		return (NULL);
	while (tmp_val[i] != '=')
		i++;
	i++;
	pair->key = env_dup(tmp_val, i, j);
	if (!pair->key)
		return (NULL);
	j = i;
	while (tmp_val[i])
		i++;
	pair->value = env_dup(tmp_val, i, j);
	if (!pair->value)
		return (NULL);
	free(tmp_val);
	return (pair);
}

t_env	*start(char **env)
{
	t_env	*my_env;
	char	*tmp_value;

	my_env = malloc(sizeof(t_env));
	if (!my_env)
		return (NULL);
	tmp_value = ft_strdup(env[0]);
	my_env->pair = init_pair(tmp_value);
	if (!my_env->pair)
		return (NULL);
	my_env->next = 0;
	return (my_env);
}

int	env_init(t_pipe_line *pipeline, char **env)
{
	int		i;
	char	*tmp_value;
	t_env	*my_env;
	t_env	*new;

	my_env = start(env);
	if (!my_env)
		return (0);
	pipeline->env = my_env;
	i = 1;
	while (env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		tmp_value = ft_strdup(env[i]);
		new->pair = init_pair(tmp_value);
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
		if (printf("%s%s\n", env->pair->key, env->pair->value))
			env = env->next;
}
