/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:56:48 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/18 00:28:31 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	signalsecho(void)
{
	struct termios		terminal;

	if (tcgetattr(STDOUT_FILENO, &terminal) == -1)
		return (-1);
	terminal.c_lflag |= ~ISIG;
	terminal.c_cc[VSUSP] = 0;
	terminal.c_lflag ^= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &terminal);
	return (0);
}

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
	pair->key = env_dup(tmp_val, i, j);
	if (!pair->key)
		return (NULL);
	j = ++i;
	while (tmp_val[i])
		i++;
	pair->value = env_dup(tmp_val, i, j);
	if (!pair->value)
		return (NULL);
	free(tmp_val);
	return (pair);
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

t_data	*init_data(int ac, char **av, t_data *data, char **envp)
{
	(void)ac;
	(void)av;
	if (!data)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (NULL);
		data->exit = 0;
		data->env = get_env(envp);
		data->exp = get_env(envp);
	}
	shelvl(&data->env);
	shelvl(&data->exp);
	sort_exp(&data->exp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	signalsecho();
	return (data);
}
