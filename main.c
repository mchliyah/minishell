/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/12 23:30:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_status;


void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 1;
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

void	extend_main(char *str_rln, t_data *data, t_p_line *pipeline)
{
	int	status;
	int	i;
	int	fd;

	add_history(str_rln);
	if (generate_token(str_rln, &pipeline, &data) != 1)
	{
		signal(SIGINT, SIG_IGN);
		init_pipes(&data);
		fd = dup(1);
		iterator(pipeline, &data);
		i = 0;
		while (i < data->pip_nb * 2)
			close(data->p_fd[i++]);
		if (fd > 0)
		{
			dup2(fd, 1);
			close(fd);
		}
		while (wait(&status) > 0)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					printf("Quit\n");
				g_status = 128 + WTERMSIG(status);
			}
		}
		free_pipe(pipeline);
		signal(SIGINT, handle_sigint);
	}
}

int SignalsEcho(void)
{
	struct termios		terminal;
 
	if(tcgetattr(STDOUT_FILENO, &terminal)== -1)
		return -1;
	terminal.c_lflag |= ~ISIG;
	terminal.c_cc[VSUSP] = 0;
	terminal.c_lflag ^= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &terminal);
	return 0;
}

int	main(int ac, char **av, char **envp)
{
	t_p_line	*pipeline;
	char		*str_rln;
	t_data		*data;

	data = NULL;
	pipeline = malloc(sizeof(t_p_line));
	data = init_data(ac, av, data, envp);
	if (!data)
		return (1);
	g_status = 0;
	data = init_data(ac, av, data, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	//SignalsEcho();
	while (!data->exit)
	{
		str_rln = readline("~minishell:~");
		if (!str_rln)
			break ;
		if (*str_rln)
			extend_main(str_rln, data, pipeline);
		else if (*str_rln == '\0')
			g_status = 0;
	}
	if (str_rln)
	{
		free(pipeline);
		free_data(data);
	}
	// rl_clear_history();
	return (g_status);
}
