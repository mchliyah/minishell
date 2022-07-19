/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/27 22:20:38 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*advance(t_lexer *lexer)
{
	lexer->i++;
	lexer->c = lexer->content[lexer->i];
	return (lexer);
}

int	ft_is_symbol(char c)
{
	if (c == EPIPE || c == LESS || c == GREATER || c == SPACE || c == '\0')
		return (1);
	return (0);
}

// !'ptr' should free inside the function
char	*join_string(char *ptr, char c)
{
	char	*j_str;
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	ft_bzero(str, 2);
	str[0] = c;
	j_str = ft_strjoin(ptr, str);
	if (!j_str)
		return (NULL);
	free(str);
	free(ptr);
	str = NULL;
	ptr = NULL;
	return (j_str);
}

//char	has_next(t_lexer *it)
//{
//	t_lexer	*this;
//
//	this = it;
//	this->i++;
//	this->c = this->content[this->i];
//	return (this->c);
//}
/*
 *   -------------------------------------
 * 	 function for member of get_char() !!
 * 	 -----------------------------------
  	 !  "ls""| pwd  should be fixed
 */
char	*get_inside_quotes(t_lexer **it)
{
	int		q;
	char	tmp;
	char	*ptr;

	ptr = NULL;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	q = 0;
	while ((*it)->c != '\0')
	{
		ptr = join_string(ptr, (*it)->c);
		tmp = (*it)->c;
		if (tmp == SINGLE_QUOTE || tmp == L_DOUBLE_QUOTE)
			q++;
		*it = advance(*it);
		if ((tmp == SINGLE_QUOTE || tmp == L_DOUBLE_QUOTE)
			&& ((*it)->c == SPACE || (*it)->c == LESS
				|| (*it)->c == EPIPE || (*it)->c == GREATER))
			break ;
		else if ((q % 2 == 0 || q == 0) && ((*it)->c == SPACE
				|| (*it)->c == LESS || (*it)->c == EPIPE
				|| (*it)->c == GREATER))
			break ;
	}
	return (ptr);
}

char	**check_for_args(t_lexer **lex)
{
	char	*str;
	int		q;
	int		start;
	int		end;

	q = 0;
	if ((*lex)->c == SPACE)
	{
		while ((*lex)->c == SPACE)
			*lex = advance(*lex);
	}
	start = (*lex)->i;
	end = (*lex)->i;
	while ((*lex)->c != '\0')
	{
		if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOUBLE_QUOTE)
			q++;
		else if (((*lex)->c == EPIPE || (*lex)->c == LESS
				|| (*lex)->c == GREATER || (*lex)->c == '\0')
			&& (q == 0 || q % 2 == 0))
		{
			end = (*lex)->i;
			break ;
		}
		*lex = advance(*lex);
	}
	if ((*lex)->c == EOS)
		end = (*lex)->i;
	str = ft_substr((*lex)->content, start, end - start);
	if (!str)
		printf("a Null returned in ft_substr in check_for_args\n");
	return (ft_split_arg(str, ' '));
}

t_token	*get_char(t_lexer **lex)
{
	char	*ptr;
	char	**str;
	char	*tmp;

	str = NULL;
	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOUBLE_QUOTE)
		ptr = get_inside_quotes(lex);
	else
	{
		ptr = ft_strdup("");
		if (!ptr)
			return (NULL);
		while ((*lex)->c != '\0')
		{
			ptr = join_string(ptr, (*lex)->c);
			*lex = advance(*lex);
			if ((*lex)->c == SPACE || (*lex)->c == EPIPE || (*lex)->c == LESS
				|| (*lex)->c == GREATER)
				break ;
			else if (((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOUBLE_QUOTE)
				&& (*lex)->c != '0')
			{
				tmp = get_inside_quotes(lex);
				ptr = ft_strjoin(ptr, tmp);
				free(tmp);
				break ;
			}
		}
	}
	str = check_for_args(lex);
	if (!str)
		printf("there is a problem occurred inside split\n");
	return (init_token(ptr, WORD, str));
}