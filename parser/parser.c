/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/01 22:45:08 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*copy_list(t_list *ret, t_list *to_copy)
{
	while (to_copy && to_copy->content->type != PIPE)
	{
		if (!ret)
			ret = ft_lstnew(to_copy->content);
		else
			ft_lstadd_back(&ret, ft_lstnew(to_copy->content));
		to_copy = to_copy->next;
	}
	return (ret);
}

t_pipe_line	*frst_pipe(t_pipe_line	*pipeline, t_list *lst_token)
{
	t_list		*left;

	pipeline->type = lst_token->content->type;
	pipeline->right = NULL;
	pipeline->left = NULL;
	pipeline->left_p = NULL;
	pipeline->right = copy_list(pipeline->right, lst_token->next);
	left = lst_token->prev;
	while (left->prev != NULL)
		left = left->prev;
	pipeline->left = copy_list(pipeline->left, left);
	return (pipeline);
}

t_pipe_line	*to_pipe(t_list *lst_token, t_pipe_line	*pipeline, int frst_p)
{
	t_pipe_line	*ret_pipe;

	ret_pipe = NULL;
	if (frst_p)
		return (frst_pipe(pipeline, lst_token));
	else
	{
		ret_pipe = malloc(sizeof(t_pipe_line));
		ret_pipe->type = lst_token->content->type;
		ret_pipe->env = pipeline->env;
		ret_pipe->right = NULL;
		ret_pipe->left = NULL;
		ret_pipe->left_p = NULL;
		ret_pipe->right = copy_list(ret_pipe->right, lst_token->next);
		ret_pipe->left_p = pipeline;
	}
	return (ret_pipe);
}

t_pipe_line	*simple_cmd(t_pipe_line *pipeline, t_list *lst_token)
{
	t_list	*tmp;

	tmp = lst_token;
	pipeline->type = WORD;
	pipeline->right = NULL;
	pipeline->left = NULL;
	pipeline->left_p = NULL;
	pipeline->left = copy_list(pipeline->left, tmp);
	return (pipeline);
}

t_pipe_line	*parse_to_tree(t_pipe_line *pipeline, t_list *lst_token)
{
	t_list		*to_free;
	int			frst_pipe;

	frst_pipe = 1;
	to_free = lst_token;
	error_check(lst_token);
	if (pipe_exist(lst_token))
	{
		while (lst_token)
		{
			if (lst_token->content->type == PIPE)
			{
				pipeline = to_pipe(lst_token, pipeline, frst_pipe);
				frst_pipe = 0;
			}
			lst_token = lst_token->next;
		}
		free_lst(lst_token);
	}
	else
		pipeline = simple_cmd(pipeline, lst_token);
	return (pipeline);
}
