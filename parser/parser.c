/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/14 01:33:10 by mchliyah         ###   ########.fr       */
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
		//free_list(lst_token);
	}
	else
		simple_cmd(pipeline, lst_token);
	//free_list(lst_token);
	return (*pipeline);
}

int	check_token(t_token *token, t_data **data, int was_rd)
{
	if (!token)
		return (0);
	token = scan_errs(token, (*data)->env, was_rd);
	if (!token)
		return (0);
	return (2);
}

int	is_rederiction(t_token *token)
{
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == LESSGREAT
		|| token->type == REDIRECT_OUT_IN_APPEND_MD)
		return (true);
	return (false);
}
int	generate_token(char *rln_str, t_p_line **pipeline, t_data **data)
{
	t_gen_tok	var;

	var.lexer = NULL;
	var.lst_token = NULL;
	var.first = 1;
	var.lexer = init_lex(var.lexer, rln_str);
	if (!var.lexer)
		return (EXIT_FAILURE);
	var.was_rederection = 0;
	while (var.lexer->i < var.lexer->str_len)
	{
		var.token = get_token(&var.lexer, var.first, var.was_rederection);
		if (!check_token(var.token, data, var.was_rederection))
			return (EXIT_FAILURE);
		var.was_rederection = 0;
		if (var.token->type == DELIMITER)
			var.was_rederection = 2;
		else if (is_rederiction(var.token))
			var.was_rederection = 1;
		var.first = 0;
		var.lst_token = linked_token(var.lst_token, var.token);
	}
	free(var.lexer);
	if (!check_gaven_file_rd(var.lst_token))
		return (EXIT_FAILURE);
	*pipeline = to_tree(pipeline, var.lst_token, data);
	return (EXIT_SUCCESS);
}
