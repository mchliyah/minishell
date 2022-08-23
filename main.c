/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/23 00:08:33 by mchliyah         ###   ########.fr       */
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
				printf("^\\Quit: %d\n", status);
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

void	get_tkn_exec(char *str_rln, t_data **data, t_p_line **pipeline)
{
	int		count;
	int		fd0;
	int		fd1;

	add_history(str_rln);
	if (generate_token(str_rln, pipeline, data) != 1)
	{
		signal(SIGINT, SIG_IGN);
		count = count_here((*data)->lst_tok);
		init_pipes(data);
		fd0 = dup(0);
		fd1 = dup(1);
		iterator(*pipeline, data);
		main_parent_waiting(count, data);
		wait_status();
		dup_std_fd(fd0, fd1);
		free_parser_data(data);
		signal(SIGINT, handle_sigint);
	}
}

t_p_line	*initpipeline(void)
{
	t_p_line	*pipeline;

	pipeline = malloc(sizeof(t_p_line));
	pipeline->left = NULL;
	pipeline->left_p = NULL;
	pipeline->right = NULL;
	return (pipeline);
}
void	parser_main(char *str_rln, t_data **data)
{
	t_p_line	*pipeline;

	while (!(*data)->exit)
	{
		str_rln = readline("~mi🙂nish🙂ell:~ ");
		if (!str_rln)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		pipeline = initpipeline();
		if (*str_rln)
		{
			get_tkn_exec(str_rln, data, &pipeline);
			free_pipe(pipeline);
			free_list((*data)->lst_tok);
		}
		else if (*str_rln == '\0')
		{
			g_status = 0;
			free(pipeline);
		}
		free(str_rln);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*str_rln;
	t_data		*data;

	data = NULL;
	str_rln = NULL;
	data = init_data(ac, av, data, envp);
	if (!data)
		return (1);
	g_status = 0;
	parser_main(str_rln, &data);
	free_data(data);
	return (g_status);
}
