/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 12:28:23 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/02 12:28:26 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	my_test(t_lexer *lexer)
{
	int			a;
	t_token		*token;

	a = -1;
	while (lexer->i < lexer->str_len)
	{
		token = get_token(lexer);
		printf("b=> %s\n", token->content);
		if (token->args)
		{
			while (token->args[++a])
				printf("b_arg[%d] ==> %s\n", a, token->args[a]);
		}
		if (!token)
			return (1);
		printf("a=> %s\n", token->content);
		a = -1;
		if (token->args)
		{
			while (token->args[++a])
				printf("a_arg[%d] ==> %s\n", a, token->args[a]);
		}
	}
	return (0);
}