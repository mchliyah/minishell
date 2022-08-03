/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/03 23:55:58 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
  ?? this comments for anything under generate_token function !!
 	if you want to add function under this function
 	you should add a condition for it
 	!! if (generate... != 1) then do what you want
 	else if generate .. == 1 means that there is unclosed
	quote or single quote !!
 */

void	to_free(t_pipe_line *pipeline)
{
	while (pipeline->left_p)
	{
		free(pipeline->right->content);
		free(pipeline->right);
		pipeline = pipeline->left_p;
	}
	if (pipeline->right)
	{
		free(pipeline->right->content->arg);
		free(pipeline->right->content->content);
		free(pipeline->right->content);
		free(pipeline->right);
	}
	if (pipeline->left)
	{
		free(pipeline->left->content->arg);
		free(pipeline->left->content->content);
		free(pipeline->left->content);
		free(pipeline->left);
	}
}

t_data	*init_data(int ac, char **av, t_data *data, char **envp)
{
	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->exit = 0;
	data->p_fd = NULL;
	data->fd_in = NULL;
	data->fd_out = NULL;
	data->env = get_env(envp);
	data->exp = get_env(envp);
	sort_exp(&data->exp);
	return (data);
}

int	init_pipes(t_data **exec)
{
	int			i;

	(*exec)->cmd_i = 0;
//	printf("pipe_nb%d\n", (*exec)->pip_nb);
	(*exec)->p_in = 0;
	if ((*exec)->pip_nb != 0)
	{
		(*exec)->p_fd = malloc((2 * (*exec)->pip_nb) * sizeof(int ));
		i = 0;
		while (i < (*exec)->pip_nb)
		{
			if (pipe((*exec)->p_fd + i * 2) < 0)
			{
				perror("couldn't pipe");
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe_line	*pipeline;
	char		*str_rln;
	t_data		*data;

	data = NULL;
	pipeline = malloc(sizeof(t_pipe_line));
	data = init_data(ac, av, data, envp);
	g_status = 0;
	while (!data->exit)
	{
		str_rln = readline("\033[1;31m ~minishell~: \033[0m");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
			if (data)
			{
				add_history(str_rln);
				if (generate_token(str_rln, &pipeline, data->env, &data) != 1)
				{
					init_pipes(&data);
					iterator(pipeline, envp, &data);
					to_free(pipeline);
				}
			}
		}
	}
	printf("exit\n");
	return (0);
}
