/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:30 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/27 22:20:51 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

t_lexer	*advance(t_lexer *lexer)
{
	lexer->i++;
	lexer->c = lexer->content[lexer->i];
	return (lexer);
}

t_token	*init_token(char *str, int type, t_arg *args)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = str;
	token->arg = args;
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
