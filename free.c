/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/22 20:35:52 by mchliyah         ###   ########.fr       */
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
		HERE;
		lst = to_f;
		to_f = to_f->next;
		if (lst->content)
		{
			free_args(lst);
			if (lst->content->content)
			{
				HERE;
				free(lst->content->content);
				lst->content->content = NULL;
			}
			free(lst->content);
			lst->content = NULL;
		}
		free(lst);
		lst = NULL;
	}
}

void	free_pipe(t_p_line *pipeline)
{
	t_p_line	*tmp;

	if (pipeline)
	{
		while (pipeline->left_p)
		{
			HERE;
			tmp = pipeline;
			free(pipeline->right);
			pipeline->right = NULL;
			pipeline = pipeline->left_p;
			free(tmp);
			tmp = NULL;
		}
		if (pipeline->right)
		{
			HERE;
			free(pipeline->right);
			pipeline->right = NULL;
		}
		if (pipeline->left)
		{
			HERE;
			free(pipeline->left);
			pipeline->left = NULL;
		}
		free(pipeline);
		pipeline = NULL;
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
