/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/19 18:57:24 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_status;

void	wait_status(void)
{
	int	status;

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
}

void	dup_std_fd(int fd0, int fd1)
{
	if (fd0 > 0)
	{
		dup2(fd0, 0);
		close(fd0);
	}
	if (fd1 > 0)
	{
		dup2(fd1, 1);
		close(fd1);
	}
}

void	get_tkn_exec(char *str_rln, t_data *data, t_p_line *pipeline)
{
	int		i;
	int		count;
	int		fd0;
	int		fd1;
	t_list	*lst;

	add_history(str_rln);
	if (generate_token(str_rln, &pipeline, &data) != 1)
	{
		signal(SIGINT, SIG_IGN);
		lst = data->lst_tok;
		count = count_here(lst);
		init_pipes(&data);
		fd0 = dup(0);
		fd1 = dup(1);
		iterator(pipeline, &data);
		i = 0;
		while (i < data->pip_nb * 2)
			close(data->p_fd[i++]);
		i = -1;
		while (++i < count)
		{
			close(data->here_fd[i][0]);
			close(data->here_fd[i][1]);
		}
		wait_status();
		dup_std_fd(fd0, fd1);
		free_parser_data(&data);
		signal(SIGINT, handle_sigint);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_p_line	*pipeline;
	char		*str_rln;
	t_data		*data;

	data = NULL;
	data = init_data(ac, av, data, envp);
	if (!data)
		return (1);
	g_status = 0;
	data = init_data(ac, av, data, envp);
	while (!data->exit)
	{
		pipeline = malloc(sizeof(t_p_line));
		str_rln = readline("~mi🙂nish🙂ell:~");
		if (!str_rln)
			break ;
		if (*str_rln)
			get_tkn_exec(str_rln, data, pipeline);
		else if (*str_rln == '\0')
			g_status = 0;
		free (str_rln);
		free_list(data->lst_tok);
		free_pipe(pipeline);
		free(pipeline);
		pipeline = NULL;
	}
	free(pipeline);
	free_data(data);;
	return (g_status);
}
