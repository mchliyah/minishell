/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/22 00:09:19 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// ! if we have a PIPE
//t_pipe_line	*pipe_line(t_list *token)
//{
//
//}
//openning file descreptors
t_pipeline	*frst_pipe(t_list *lst_token, t_pipe_line	*pipeline)
{
	t_pipe_line	*ret_pipe;
	t_list		*tmp;
	t_list		*tmp1;

	ret_pipe = malloc(sizeof(t_pipe_line));
	tmp = lst_token;
	pipeline->type = tmp->content->type;
	pipeline->right = tmp->next;
	while (tmp->next->content->type != PIPE)
		tmp = tmp->next;
	tmp->next = NULL;
	tmp1 = lst_token->prev;
	tmp->next = NULL;
	while (tmp1->prev != NULL)
		lst_token = lst_token->prev;
	pipeline->left = tmp1->next;
	return (ret_pipe);
}

t_pipe_line	*to_pipe(t_list *lst_token, t_pipe_line	*pipeline, int frst_p)
{
	t_pipe_line	*ret_pipe;
	t_list		*tmp;
	t_list		*tmp1;

	if (frst_p)
		pipeline = frst_pipe(lst_token, pipeline);
	else
	{
		ret_pipe = malloc(sizeof(t_pipe_line));
		tmp = lst_token;
		ret_pipe->type = tmp->content->type;
		ret_pipe->right = tmp->next;
		while (tmp->next->content->type != PIPE)
			tmp = tmp->next;
		tmp->next = NULL;
		ret_pipe->left = pipeline;
	}
	return (ret_pipe);
}

// will return a parsed tree
t_pipe_line	*parse_to_tree(t_list *lst_token)
{
	t_list		*to_free;
	t_pipe_line	*pipeline;
	int			frst_pipe;

	frst_pipe = 1;
	to_free = lst_token;
	pipeline = malloc(sizeof(t_pipe_line));
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
		return (NULL);
	return (pipeline);
}
