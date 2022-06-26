/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:30 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/26 14:17:31 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

t_token	*init_token(char *str, int type, char *args)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = str;
	token->args = args;
	return (token);
}

t_lexer	*init_lex(t_lexer *lex, char *rln_str)
{
	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL);
	lex->content = rln_str;
	lex->i = 0;
	lex->str_len = ft_strlen(rln_str);
	lex->c = lex->content[lex->i];
	return (lex);
}
