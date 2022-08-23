/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:25:25 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/23 15:25:26 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_for_variables(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (true);
	}
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
