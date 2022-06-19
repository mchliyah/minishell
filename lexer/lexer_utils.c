/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/19 20:51:27 by mchliyah         ###   ########.fr       */
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

int	ft_is_symbol(char c)
{
	if (c == EPIPE || c == LESS || c == GREATER || c == SPACE || c == '\0')
		return (1);
	return (0);
}

char	*check_for_args(t_lexer **this, int i)
{
	char	*ptr;
	char	*str;

	ptr = NULL;
	if ((*this)->c == SPACE)
		*this = advance(*this);
	if (!ft_is_symbol((*this)->c))
		ptr = ft_strdup("");
	while ((*this)->c != '\0')
	{
		if (i != 0)
			break;
		str = malloc(2 * sizeof(char));
		ft_bzero(str, 2);
		str[0] = (*this)->c;
		ptr = ft_strjoin(ptr, str);
		free(str);
		*this = advance(*this);
	}
	return (ptr);
}
int	check_qoute(char cu, char c, int i)
{
	if (ft_strchr(SYMBOLS, cu) && (i == 0 || i%2==0))
		return (1);
	else if ((c == SINGLE_QUOTE || c == L_DOBLE_QUOTE) && cu == SPACE && i%2 == 0)
		return (1);
	return (0);
}
t_token *get_char(t_lexer **lex)
{
	char	h;
	int 	i;
	char	*ptr;
	char	*str;

	i = 0;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while ((*lex)->c != '\0' && ft_isprint((*lex)->c))
	{
		if (ft_strchr("\"\'",(*lex)->c))
			i++;
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
		h  = (*lex)->c;
		*lex = advance(*lex);
		if (check_qoute((*lex)->c, h, i)) {
			break ;
		}
	}
//	if (i%2 == 1)
//	{
//		printf("cmd %s   err %c\n", ptr, L_DOBLE_QUOTE);
//		exit(0);
//	}
	// str = check_for_args(lex);
	str = check_for_args(lex, i);
	return (init_token(ptr, WORD, str));
}