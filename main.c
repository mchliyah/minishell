/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/14 01:26:42 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int g_status;

/*
  ?? this comments for anything under generate_token function !!
 	if you want to add function under this function
 	you should add a condition for it
 	!! if (generate... != 1) then do what you want
 	else if generate .. == 1 means that there is unclosed
	quote or single quote !!
 */



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

	fd = dup(1);
	add_history(str_rln);
	if (generate_token(str_rln, &pipeline, &data) != 1)
	{
		init_pipes(&data);
		check_for_heredoc(pipeline, &data);
		iterator(pipeline, &data);
		i = 0;
		while (i < data->pip_nb * 2)
			close(data->p_fd[i++]);
		while (wait(&status) > 0)
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
		if (fd > 0)
		{
			dup2(fd, 1);
			close(fd);
		}
		free_pipe(pipeline);
	}
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
	while (!data->exit)
	{
		str_rln = readline("\001\033[1;31m\002 ~minishell~ \001\033[0m\002");
		if (!str_rln)
			break ;
		if (*str_rln)
			extend_main(str_rln, data, pipeline);
		else if (*str_rln == '\0')
			g_status = 0;
	}
	free(pipeline);
	free_data(data);
	return (g_status);
}
