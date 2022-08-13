/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/14 00:39:17 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	simple_cmd(t_p_line **pipeline, t_list *lst_token)
{
	t_list	*tmp;

	tmp = lst_token;
	(*pipeline)->type = WORD;
	(*pipeline)->right = NULL;
	(*pipeline)->left = NULL;
	(*pipeline)->left_p = NULL;
	(*pipeline)->left = copy_list((*pipeline)->left, tmp);
}

t_p_line	*to_tree(t_p_line **pipeline, t_list *lst_token, t_data **data)
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
	free_list(lst_token);
	return (*pipeline);
}

int	check_token(t_token *token, t_data **data)
{
	if (!token)
		return (0);
	token = scan_errs(token, (*data)->env);
	if (!token)
		return (0);
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == LESSGREAT || token->type == DELIMITER
		|| token->type == REDIRECT_OUT_IN_APPEND_MD)
		return (1);
	return (2);
}

int	generate_token(char *rln_str, t_p_line **pipeline, t_data **data)
{
	int			first;
	int			was_rederection;
	t_token		*token;
	t_lexer		*lexer;
	t_list		*lst_token;

	lexer = NULL;
	lst_token = NULL;
	first = 1;
	lexer = init_lex(lexer, rln_str);
	if (!lexer)
		return (EXIT_FAILURE);
	was_rederection = 0;
	while (lexer->i < lexer->str_len)
	{
		token = get_token(&lexer, first, was_rederection);
		was_rederection = 0;
		if (!check_token(token, data))
			return (EXIT_FAILURE);
		else if (check_token(token, data) == 1)
			was_rederection = 1;
		first = 0;
		lst_token = linked_token(lst_token, token);
	}
	free(lexer);
	if (!check_gaven_file_rd(lst_token))
		return (EXIT_FAILURE);
	*pipeline = to_tree(pipeline, lst_token, data);
	return (EXIT_SUCCESS);
}
