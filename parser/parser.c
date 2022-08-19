/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/19 02:50:51 by mchliyah         ###   ########.fr       */
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
	}
	else
		simple_cmd(pipeline, lst_token);
	return (*pipeline);
}

int	check_token(t_token **token, t_data **data, int was_rd)
{
	if (!token)
		return (0);
	if (!scan_errs(token, (*data)->env, was_rd))
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

t_gen_tok	generate_init(char *rln_str, t_data **data)
{
	t_gen_tok	var;

	var.lexer = NULL;
	(*data)->lst_tok = NULL;
	var.first = 1;
	var.lexer = init_lex(var.lexer, rln_str);
	if (!var.lexer)
	{
		perror("malloc");
		exit(1);
	}
	var.was_rederection = 0;
	return (var);
}

int	index_heredoc(t_data **data)
{
	int		max;
	t_list	*list;
	int		indx;
	int		there;

	indx = 0;
	there = 0;
	max = 0;
	list = (*data)->lst_tok;
	while (list)
	{
		if (list->content->type == DELIMITER)
		{
			max++;
			list->content->indx = indx;
			there = 1;
		}
		else if (list->content->type == PIPE && there)
		{
			indx++;
			there = 0;
		}
		list = list->next;
	}
	return (max);
}

int	generate_token(char *rln_str, t_p_line **pipeline, t_data **data)
{
	t_arg	*a;
	t_gen_tok	var;

	var = generate_init(rln_str, data);
	while (var.lexer->i < var.lexer->str_len)
	{
		var.token = get_token(&var.lexer, var.first, var.was_rederection);
		a = var.token->arg;
		while (a)
		{
			printf("=>|%s|\n", a->content);
			a = a->next;
		}
		if (!check_token(&var.token, data, var.was_rederection))
		{
			free_lexer_var(var);
			return (EXIT_FAILURE);
		}
		var.was_rederection = 0;
		if (var.token->type == DELIMITER)
			var.was_rederection = 2;
		else if (is_rederiction(var.token))
			var.was_rederection = 1;
		var.first = 0;
		(*data)->lst_tok = linked_token((*data)->lst_tok, var.token);
	}
	free(var.lexer);
	if (index_heredoc(data) > 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		return (1);
	}
	get_here_doc((*data)->lst_tok, data);
	*pipeline = to_tree(pipeline, (*data)->lst_tok, data);
	if (!check_gaven_file_rd((*data)->lst_tok))
	{
		free_lexer_var(var);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
