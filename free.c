/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/18 23:21:54 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_list(t_list *to_f)
{
	t_arg	*arg;
	t_list	*lst;

	while (to_f)
	{
		HERE;
		lst = to_f;
		if (to_f->content)
		{
			while (to_f->content->arg)
			{
				HERE;
				arg = to_f->content->arg;
				to_f->content->arg = to_f->content->arg->next;
				HERE;
				if (arg)
				{
					free(arg->content);
					arg->content = NULL;
					free(arg);
					arg = NULL;
				}
			}
			HERE;
			if (to_f->content->content)
			{
				free(to_f->content->content);
				to_f->content->content = NULL;
			}
			free(to_f->content);
			to_f->content = NULL;
		}
		HERE;
		to_f = to_f->next;
		HERE;
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

	while (pipeline->left_p)
	{
		tmp = pipeline;
		free_list(pipeline->right);
		pipeline = pipeline->left_p;
		free(tmp);
		tmp = NULL;
	}
	if (pipeline->right)
	{
		free(pipeline->right);
		pipeline->right = NULL;
	}
	if (pipeline->left)
	{
		HERE;
		free(pipeline->left);
		pipeline->left = NULL;
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
