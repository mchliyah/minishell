/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/14 01:06:11 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	t_p_line	*tmp;

	while (pipeline->left_p)
	{
		tmp = pipeline;
		free_list(pipeline->right);
		pipeline = pipeline->left_p;
		free(tmp);
	}
	if (pipeline->right)
		free_list(pipeline->right);
	if (pipeline->left)
		free_list(pipeline->left);
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
