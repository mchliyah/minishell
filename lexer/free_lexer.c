/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:59:16 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/18 12:02:48 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parser_data(t_data **data)
{
	free((*data)->p_fd);
}

void	free_lexer_var(t_gen_tok var)
{
	free(var.lexer);
	while (var.token->arg)
	{
		free(var.token->arg->content);
		free(var.token->arg);
		var.token->arg = var.token->arg->next;
	}
	free(var.token->arg);
	free(var.token->content);
	free(var.token);
}
