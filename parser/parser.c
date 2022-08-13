/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 01:41:53 by mchliyah         ###   ########.fr       */
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

t_pipe_line	*frst_pipe(t_pipe_line	**pipeline, t_list *lst_token)
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

t_pipe_line	*to_pipe(t_list *lst_token, t_pipe_line	**pipeline, int frst_p)
{
	t_pipe_line	*ret_pipe;

	ret_pipe = NULL;
	if (frst_p)
		*pipeline = frst_pipe(pipeline, lst_token);
	else
	{
		ret_pipe = malloc(sizeof(t_pipe_line));
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

void	simple_cmd(t_pipe_line **pipeline, t_list *lst_token)
{
	t_list	*tmp;

	tmp = lst_token;
	(*pipeline)->type = WORD;
	(*pipeline)->right = NULL;
	(*pipeline)->left = NULL;
	(*pipeline)->left_p = NULL;
	(*pipeline)->left = copy_list((*pipeline)->left, tmp);
}

t_pipe_line	*parse_to_tree(t_pipe_line **pipeline, t_list *lst_token, t_data **data)
{
	int			frst_pipe;

	frst_pipe = 1;
	error_check(lst_token);
	(*data)->pip_nb = pipe_exist(lst_token);
	if ((*data)->pip_nb)
	{
		while (lst_token)
		{
			if (lst_token->content->type == PIPE)
			{
				*pipeline = to_pipe(lst_token, pipeline, frst_pipe);
				frst_pipe = 0;
			}
			lst_token = lst_token->next;
		}
		free_lst(lst_token);
	}
	else
		simple_cmd(pipeline, lst_token);
	return (*pipeline);
}

int	generate_token(char *rln_str, t_pipe_line **pipeline, t_env *env, t_data **data)
{
	int			first;
	int			was_rd;
	t_token		*token;
	t_lexer		*lexer;
	t_list		*lst_token;

	lexer = NULL;
	lst_token = NULL;
	first = 1;
	lexer = init_lex(lexer, rln_str);
	if (!lexer)
		return (EXIT_FAILURE);
    was_rd = 0;
	while (lexer->i < lexer->str_len)
	{
        token = get_token(&lexer, first, was_rd);
		if (!token)
            return (EXIT_FAILURE);
        token = scan_errs(token, env, was_rd);
        if (!token)
            return (EXIT_FAILURE);
		was_rd = 0;
        if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
			|| token->type == LESSGREAT
			|| token->type == REDIRECT_OUT_IN_APPEND_MD)
			was_rd = 1;
		if (token->type == DELIMITER)
			was_rd = 2;
		first = 0;
		lst_token = linked_token(lst_token, token);
	}
	if (!check_gaven_file_rd(lst_token))
		return (EXIT_FAILURE);
	*pipeline = parse_to_tree(pipeline, lst_token, data);
	return (EXIT_SUCCESS);
}
