/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/13 23:54:49 by mchliyah         ###   ########.fr       */
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

void	free_list(t_list *to_f)
{
	t_arg	*arg;

	while (to_f->next)
	{
		while (to_f->content->arg)
		{
			arg = to_f->content->arg;
			to_f->content->arg = to_f->content->arg->next;
			free(arg);
		}
		if (to_f->content->content)
			free(to_f->content->content);
		if (to_f->content)
			free(to_f->content);
		to_f = to_f->next;
	}
	while (to_f->prev)
	{
		free(to_f->next);
		to_f = to_f->prev;
	}
	if (to_f)
		free(to_f);
}

void	free_pipe(t_p_line *pipeline)
{
	// t_p_line	*to_f_pipe;
	// t_p_line	*prev;

	// to_f_pipe = pipeline;
	while (pipeline->left_p)
	{
		free_list(pipeline->right);
		pipeline = pipeline->left_p;
	}
	if (pipeline->right)
		free_list(pipeline->right);
	if (pipeline->left)
		free_list(pipeline->left);
	// while(to_f_pipe->left_p)
	// {
	// 	prev = to_f_pipe;
	// 	to_f_pipe = to_f_pipe->left_p;
	// 	if (prev)
	// 		free(prev);
	// }
	// if (to_f_pipe)
	// 	free(to_f_pipe);
}

void	free_env(t_env *env)
{
	t_env	*prev_env;

	while (env)
	{
		prev_env = env;
		env = env->next;
		free(prev_env->pair->key);
		free(prev_env->pair->value);
		free(prev_env->pair);
		free(prev_env);
	}

}

void	free_data(t_data *data)
{
	free_env(data->env);
	free_env(data->exp);
	free(data->p_fd);
	free(data);
}

void	shelvl(t_env **env)
{
	t_env	*tmp_env;
	int		to_set;
	char	*itoa_val;

	tmp_env = *env;
	itoa_val = NULL;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->pair->key, "SHLVL",
				ft_strlen(tmp_env->pair->key)))
		{
			to_set = ft_atoi(tmp_env->pair->value);
			free(tmp_env->pair->value);
			itoa_val = ft_itoa(to_set + 1);
			tmp_env->pair->value = ft_strdup(itoa_val);
			free(itoa_val);
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

void	check_for_heredoc(t_p_line *pipe, t_data **data)
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
	t_p_line	*pipeline;
	char		*str_rln;
	t_data		*data;
	int			status;
	int fd;

	data = NULL;
	pipeline = malloc(sizeof(t_p_line));
	data = init_data(ac, av, data, envp);
	if (!data)
		return (1);
	g_status = 0;
	while (!data->exit)
	{
		str_rln = readline("\001\033[1;31m\002 ~minishell~ \001\033[0m\002");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
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
		else if (*str_rln == '\0')
			g_status = 0;
	}
	free(pipeline);
	free_data(data);
	return (g_status);
}
