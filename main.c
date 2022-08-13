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

int g_status;

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

void	shelvl(t_env **env)
{
	t_env	*tmp_env;
	int		to_set;

	tmp_env = *env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->pair->key, "SHLVL",
				ft_strlen(tmp_env->pair->key)))
		{
			to_set = ft_atoi(tmp_env->pair->value);
			free(tmp_env->pair->value);
			tmp_env->pair->value = ft_strdup(ft_itoa(to_set + 1));
		}
		tmp_env = tmp_env->next;
	}
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
		data->p_fd = NULL;
		data->fd_in = -1;
		data->fd_out = -1;
		data->env = get_env(envp);
		data->exp = get_env(envp);
	}
	shelvl(&data->env);
	shelvl(&data->exp);
	sort_exp(&data->exp);
	return (data);
}

int	init_pipes(t_data **exec)
{
	int			i;

	(*exec)->cmd_i = 0;
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

void	get_here_doc(t_list *cmd, t_data **data)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp && tmp->next)
	{
		if (tmp->content->type == DELIMITER)
			if (!here_doc(tmp->next->content->content, data))
				return ;
		tmp = tmp->next;
	}
}

void	check_for_heredoc(t_pipe_line *pipe, t_data **data)
{
	if (pipe->left_p)
		check_for_heredoc(pipe->left_p, data);
	if (pipe->left)
		get_here_doc(pipe->left, data);
	if (pipe->right)
		get_here_doc(pipe->right, data);
}
int	main(int ac, char **av, char **envp)
{
	int			i;
	t_pipe_line	*pipeline;
	char		*str_rln;
	t_data		*data;
	int			status;
	int fd;

	data = NULL;
	pipeline = malloc(sizeof(t_pipe_line));
	data = init_data(ac, av, data, envp);
	g_status = 0;
	while (!data->exit)
	{
		str_rln = readline("\001\033[1;31m\002 ~minishell~ \001\033[0m\002");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
			if (data)
			{
				fd = dup(1);
				add_history(str_rln);
				if (generate_token(str_rln, &pipeline, data->env, &data) != 1)
				{
					init_pipes(&data);
					check_for_heredoc(pipeline, &data);
					iterator(pipeline, &data);
					i = 0;
					while (i < data->pip_nb * 2)
						close(data->p_fd[i++]);
					while (wait(&status) > 0)
					{
						if (WIFEXITED(status)) {
							g_status = WEXITSTATUS(status);
						}
					}
					if (fd > 0)
					{
						dup2(fd, 1);
						close(fd);
					}
					to_free(pipeline);
				}
			}
		}
		else if (*str_rln == '\0')
			g_status = 0;
	}
	printf("exit\n");
	return (g_status);
}
