/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:22:52 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/05 12:22:54 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//t_token	*get_token_file(t_lexer **lex)
//{
//	char	*ptr;
//
//	while ((*lex)->c == SPACE)
//		*lex = advance(*lex);
////	if ((*lex)->c == L_DOUBLE_QUOTE)
////		ptr = get_inside_quotes(lex);
////	else if ((*lex)->c == SINGLE_QUOTE)
////		ptr = get_inside_s_quotes(lex);
//	ptr = ft_strdup("");
//	if (!ptr)
//		return (NULL);
//	while ((*lex)->c != '\0')
//	{
//		//printf("%c\n", (*lex)->c);
//		ptr = join_string(ptr, (*lex)->c);
//		*lex = advance(*lex);
//		if ((*lex)->c == SPACE || (*lex)->c == EPIPE || (*lex)->c == LESS
//		|| (*lex)->c == GREATER)
//			break ;
////		else if (((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOUBLE_QUOTE)
////		&& (*lex)->c != '0')
////		{
////			if ((*lex)->c == L_DOUBLE_QUOTE)
////				tmp = get_inside_quotes(lex);
////			else
////				tmp = get_inside_s_quotes(lex);
////			ptr = ft_strjoin(ptr, tmp);
////			free(tmp);
////			break ;
////		}
//	}
//	return (init_token(ptr, WORD, NULL));
//}

