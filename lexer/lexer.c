/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:10:35 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/16 10:10:37 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*advance(t_lexer *lexer)
{
	if (lexer->i < lexer->str_len)
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
	return (lexer);
}
/*
 *exp:
 * 			echo hello
 * 			OR   echo "hel lo"
 * 			OR   ls -la
 * 			OR   ls -l -a
 * 			OR   echo "$HOME" which is variable
 * 			OR	 echo $HOME
 * 			Or 	 echo 'hel lo'  - which print on terminal - hel lo
 * 			OR	  echo '$HOME' 	- which print on terminal - $HOME
 *
 */
char	*check_for_args(t_lexer **this)
{
	char	*ptr;
	char	*str;

	if ((*this)->c == SPACE)
		*this = advance(*this);
	if ((*this)->c == SINGLE_QUOTE || (*this)->c == L_DOBLE_QUOTE)
		*this = advance(*this);
	if ((*this)->c != EPIPE && (*this)->c != LESS && (*this)->c != GREATER)
	{
		ptr = ft_strdup("");
		while ((*this)->c != '\0')
		{
			if ((*this)->c == SINGLE_QUOTE || (*this)->c == R_DOBLE_QUOTE)
				*this = advance(*this);
			str = malloc(2 * sizeof(char));
			ft_bzero(str, 2);
			str[0] = (*this)->c;
			ptr = ft_strjoin(ptr, str);
			free(str);
			*lex = advance(*lex);
		}
	}
}

t_token *get_char(t_lexer **lex)
{
	char	*ptr;
	char	*str;

	ptr = ft_strdup("");
	while ((*lex)->c != '\0' && ft_isalpha((*lex)->c))
	{
		str = malloc(2 * sizeof(char));
		ft_bzero(str, 2);
		str[0] = (*lex)->c;
		ptr = ft_strjoin(ptr, str);
		free(str);
		*lex = advance(*lex);
	}
	check_for_args(lex);
	return (init_token(ptr, WORD));
}

t_token	*get_pipe(t_lexer **lex)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	ft_bzero(str, 2);
	str[0] = (*lex)->c;
	*lex = advance(*lex);
	return init_token(str, PIPE);
}
t_token 	*get_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == SPACE)
			advance(lexer);
		else if (ft_isalpha(lexer->c))
			return (get_char(&lexer));
		else if (lexer->c == EPIPE)
			return (get_pipe(&lexer));
//		else if (lexer->c == LESS)
//			return (get_)
	}
	return (NULL);
}

int generate_token(char *rln_str)
{
	t_token *token;
	t_lexer	*lexer;

	lexer = NULL;
	lexer = init_lex(lexer, rln_str);
	token = get_token(lexer);
	printf("%s\n", token->content);
	token= get_token(lexer);
	printf("%s\n", token->content);
	return (EXIT_SUCCESS);
}
