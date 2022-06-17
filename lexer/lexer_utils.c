/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/17 09:50:38 by ael-mous         ###   ########.fr       */
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

//char	*check_for_args(t_lexer **this)
//{
//	char	*ptr;
//	char	*str;
//
//	if ((*this)->c == SPACE)
//		*this = advance(*this);
//	if ((*this)->c == SINGLE_QUOTE || (*this)->c == L_DOBLE_QUOTE)
//		*this = advance(*this);
//	if ((*this)->c != EPIPE && (*this)->c != LESS && (*this)->c != GREATER)
//	{
//		ptr = ft_strdup("");
//		while ((*this)->c != '\0')
//		{
//			if ((*this)->c == SINGLE_QUOTE || (*this)->c == R_DOBLE_QUOTE)
//				*this = advance(*this);
//			str = malloc(2 * sizeof(char));
//			ft_bzero(str, 2);
//			str[0] = (*this)->c;
//			ptr = ft_strjoin(ptr, str);
//			free(str);
//			*this = advance(*this);
//		}
//	}
//	return ptr;
//}

t_token *get_char(t_lexer **lex)
{
	int 	i;
	char	*ptr;
	char	*str;

	i = 0;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
	{
		*lex = advance(*lex);
		i++;
	}
	while ((*lex)->c != '\0' && ft_isalpha((*lex)->c))
	{
		if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
		{
			*lex = advance(*lex);
			i++;
		}
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
		ft_bzero(str, 2);
		str[0] = (*lex)->c;
		ptr = ft_strjoin(ptr, str);
		if (!ptr)
			return (NULL);
		free(str);
		str = NULL;
		*lex = advance(*lex);
		if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
		{
			*lex = advance(*lex);
			i++;
		}
	}
	if (i%2 == 1)
	{
		printf("cmd %s   err %c\n", ptr, L_DOBLE_QUOTE);
		exit(0);
	}
//	str = check_for_args(lex);
	return (init_token(ptr, WORD, str));
}