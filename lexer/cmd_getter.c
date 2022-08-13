///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   cmd_getter.c                                       :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2022/08/13 19:42:36 by ael-mous          #+#    #+#             */
///*   Updated: 2022/08/13 19:42:38 by ael-mous         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../includes/minishell.h"
//
//
//char	*get_inside_quotes(t_lexer **it)
//{
//	int		q;
//	char	tmp;
//	char	*ptr;
//
//	ptr = NULL;
//	ptr = ft_strdup("");
//	if (!ptr)
//		return (NULL);
//	q = 0;
//	while ((*it)->c != '\0')
//	{
//		ptr = join_string(ptr, (*it)->c);
//		tmp = (*it)->c;
//		if (tmp == L_DOUBLE_QUOTE)
//			q++;
//		*it = advance(*it);
//		if (tmp == L_DOUBLE_QUOTE
//			&& ((*it)->c == SPACE || (*it)->c == LESS
//				|| (*it)->c == EPIPE || (*it)->c == GREATER
//				|| (*it)->c == SINGLE_QUOTE) && (q % 2 == 0 || q == 0))
//			break ;
//	}
//	return (ptr);
//}
//
//char	*get_inside_s_quotes(t_lexer **it)
//{
//	int		q;
//	char	tmp;
//	char	*ptr;
//
//	ptr = NULL;
//	ptr = ft_strdup("");
//	if (!ptr)
//		return (NULL);
//	q = 0;
//	while ((*it)->c != '\0')
//	{
//		ptr = join_string(ptr, (*it)->c);
//		tmp = (*it)->c;
//		if (tmp == SINGLE_QUOTE)
//			q++;
//		*it = advance(*it);
//		if (tmp == SINGLE_QUOTE
//			&& ((*it)->c == SPACE || (*it)->c == LESS
//				|| (*it)->c == EPIPE || (*it)->c == GREATER)
//			&& (q % 2 == 0 || q == 0))
//			break ;
//	}
//	return (ptr);
//}
//
//char	*cmd_getter(t_lexer **lex)
//{
//	char	*ptr;
//
//	ptr = NULL;
//	if ((*lex)->c == R_DOUBLE_QUOTE)
//	{
//		ptr = get_quote_things(lex);
//		while ((*lex)->content[(*lex)->i + 1] == L_DOUBLE_QUOTE)
//		{
//			*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_quote_things(lex));
//		}
//		if (ft_isalnum((*lex)->content[(*lex)->i + 1]))
//		{
//			*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_s_word(lex));
//		}
//		while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
//		{
//			*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_s_quote_things(lex));
//		}
//	}
//	else if ((*lex)->c == SINGLE_QUOTE)
//	{
//		ptr = get_s_quote_things(lex);
//		while ((*lex)->content[(*lex)->i + 1] == SINGLE_QUOTE)
//		{
//			*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_quote_things(lex));
//		}
//		if (ft_isalnum((*lex)->content[(*lex)->i]))
//		{
//			*lex = advance(*lex);
//			ptr = ft_strjoin(ptr, get_s_word(lex));
//		}
//	}
//	else
//		ptr = get_s_word(lex);
//	return (ptr);
//}