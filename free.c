/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 20:49:22 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_args(t_list *to_f)
{
	t_arg	*arg;

	while (to_f->content->arg)
	{
		arg = to_f->content->arg;
		to_f->content->arg = to_f->content->arg->next;
		if (arg)
		{
			free(arg->content);
			arg->content = NULL;
			free(arg);
			arg = NULL;
		}
	}
}

void	free_list(t_list *to_f)
{
	t_list	*lst;

	while (to_f)
	{
		lst = to_f;
		if (to_f->content)
		{
			free_args(to_f);
			if (to_f->content->content)
			{
				free(to_f->content->content);
				to_f->content->content = NULL;
			}
			free(to_f->content);
			to_f->content = NULL;
		}
		to_f = to_f->next;
		if (lst)
		{
			free(lst);
			lst = NULL;
		}
	}
}

void	free_pipe(t_p_line *pipeline)
{
	t_p_line	*tmp;

	if (pipeline)
	{
		while (pipeline->left_p)
		{
			tmp = pipeline;
			free_list(pipeline->right);
			pipeline->right = NULL;
			pipeline = pipeline->left_p;
			free(tmp);
			tmp = NULL;
		}
		if (pipeline->right)
		{
			free_list(pipeline->right);
			pipeline->right = NULL;
		}
		if (pipeline->left)
		{
			free_list(pipeline->left);
			pipeline->left = NULL;
		}
	}
}

void	free_env(t_env *env)
{
	t_env	*prev_env;

	while (env)
	{
		prev_env = env;
		env = env->next;
		free(prev_env->pair->key);
		if (prev_env->pair->value)
			free(prev_env->pair->value);
		free(prev_env->pair);
		free(prev_env);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	free_env(data->env);
	free_env(data->exp);
	while (i < data->here_size)
		free(data->here_fd[i++]);
	if (data->here_size)
		free(data->here_fd);
	free(data);
}
