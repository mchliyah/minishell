/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:57:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/23 13:09:46 by mchliyah         ###   ########.fr       */
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

void	free_pip_list(t_list *lst)
{
	while (lst->next)
	{
		lst = lst->next;
		free(lst->prev);
		lst->prev = NULL;
	}
	free(lst);
	lst = NULL;
}

void	free_list(t_list *to_f)
{
	t_list	*lst;

	while (to_f)
	{
		lst = to_f;
		to_f = to_f->next;
		if (lst->content)
		{
			free_args(lst);
			if (lst->content->content)
			{
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
			tmp = pipeline;
			free_pip_list(pipeline->right);
			pipeline = pipeline->left_p;
			free(tmp);
			tmp = NULL;
		}
		if (pipeline->right)
			free_pip_list(pipeline->right);
		if (pipeline->left)
			free_pip_list(pipeline->left);
		free(pipeline);
		pipeline = NULL;
	}
}

