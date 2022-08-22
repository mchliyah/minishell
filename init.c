/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:56:48 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 18:53:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_status;

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

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 1;
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
	tmp_val = NULL;
	return (pair);
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
		data->here_size = 0;
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
