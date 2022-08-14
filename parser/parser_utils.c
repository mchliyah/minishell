/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 23:44:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 23:51:08 by mchliyah         ###   ########.fr       */
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

t_p_line	*frst_pipe(t_p_line	**pipeline, t_list *lst_token)
{
	t_list		*left;

	(*pipeline)->type = lst_token->content->type;
	(*pipeline)->left = NULL;
	(*pipeline)->left_p = NULL;
	(*pipeline)->right = NULL;
	(*pipeline)->right = copy_list((*pipeline)->right, lst_token->next);
	left = lst_token->prev;
	while (left->prev != NULL)
		left = left->prev;
	(*pipeline)->left = copy_list((*pipeline)->left, left);
	return (*pipeline);
}

t_p_line	*to_pipe(t_list *lst_token, t_p_line	**pipeline, int frst_p)
{
	t_p_line	*ret_pipe;

	ret_pipe = NULL;
	if (frst_p)
		*pipeline = frst_pipe(pipeline, lst_token);
	else
	{
		ret_pipe = malloc(sizeof(t_p_line));
		ret_pipe->type = lst_token->content->type;
		ret_pipe->right = NULL;
		ret_pipe->left = NULL;
		ret_pipe->left_p = NULL;
		ret_pipe->right = copy_list(ret_pipe->right, lst_token->next);
		ret_pipe->left_p = *pipeline;
		return (ret_pipe);
	}
	return (*pipeline);
}
