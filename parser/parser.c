/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 23:12:19 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	var.token = NULL;
	// var.token->arg = NULL;
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

bool	check_syntax(t_list *list)
{
	t_list	*this;

	this = list;
	while (this)
	{
		if (!syntax_err_checker(this))
			return (false);
		this = this->next;
	}
	return (true);
}

int	extend_generate(t_data **data, t_p_line **pipeline)
{
	if (index_heredoc(data) > 16)
		if (ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2))
			exit(2);
	to_tree(pipeline, (*data)->lst_tok, data);
	if (!get_here_doc((*data)->lst_tok, data))
		return (1);
	if (!check_syntax((*data)->lst_tok))
		return (1);
	return (0);
}

void	ft_free_token(t_token *token)
{
	if (token->content)
	{
		while (token->arg)
		{
			free(token->arg->content);
			free(token->arg);
			token->arg = token->arg->next;
		}
		free(token->content);
	}
	free(token);
}

int	generate_token(char *rln_str, t_p_line **pipeline, t_data **data)
{
	t_gen_tok	var;

	var = generate_init(rln_str, data);
	(*pipeline)->left_p = NULL;
	while (var.lexer->i < var.lexer->str_len)
	{
		var.token = get_token(&var.lexer, var.first, var.was_rederection);
		if (!var.token)
		{
			free(var.lexer);
			ft_free_token(var.token);
			return (EXIT_FAILURE);
		}
		if (!check_token(&var.token, data, var.was_rederection))
		{
			free(var.lexer);
			ft_free_token(var.token);
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
	if (extend_generate(data, pipeline))
		return (1);
	return (EXIT_SUCCESS);
}
