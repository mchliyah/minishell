/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/28 19:54:35 by mchliyah         ###   ########.fr       */
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
	data->exit = 0;
	data->pip_nb = 0;
	data->pips = NULL;
	data->fdin = NULL;
	data->fdout = NULL;
	data->env = get_env(envp);
	data->exp = get_env(envp);
	// sort_exp(&data->exp);
	return (data);
}

int	count_pipes(t_pipe_line *pipes, t_exec **exec)
{
	int			a;
	int			i;
	t_pipe_line	*this;

	*exec = malloc(sizeof(t_exec));
	if (!*exec)
		return (EXIT_FAILURE);
	(*exec)->cmd_n = 0;
	this = pipes;
	a = 0;
	i = 0;
	while (this->left_p)
	{
		a++;
		this = this->left_p;
	}
	printf("aaaaaa %d\n", a);
	(*exec)->p_fd = malloc(2 * a);
	(*exec)->cmd_size = a + 1;
	(*exec)->p_index = 0;
	if (a != 0)
	{
	while (i < (a * 2))
	{
		i += 2;
		if (pipe((*exec)->p_fd + i) < 0)
		{
			perror("pipe:");
		}
	}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe_line	*pipeline;
	t_env		*env;
	t_env		*exp;
	char		*str_rln;

	pipeline = malloc(sizeof(t_pipe_line));
	data = malloc(sizeof(t_data));
	data = init_data(ac, av, data, envp);
	while (!data->exit)
	{
		str_rln = readline("\033[1;31m ~minishell~: \033[0m");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
			add_history(str_rln);
			if (generate_token(str_rln, &pipeline, data->env, &data) != 1)
			{
				printf("%d\n", data->pip_nb);
				exec_cmd(pipeline->left, &data->env, &data->exp, envp);
				count_pipes(pipeline, &exec);
				iterator(pipeline, &env, &exp, envp, exec);
				to_free(pipeline);
			}
		}
	}
	printf("exit\n");
	return (0);
}
