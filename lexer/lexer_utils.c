/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/05 22:09:25 by mchliyah         ###   ########.fr       */
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

// !'ptr'  freed inside the function
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

/*
 *   -------------------------------------
 * 	 function for member of get_char() !!
 * 	 -----------------------------------
  	 !  "ls""| pwd  should be fixed
  	 todo there is a mistake here in quote counter !!
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
		if (tmp == L_DOUBLE_QUOTE)
			q++;
		*it = advance(*it);
		if (tmp == L_DOUBLE_QUOTE
			&& ((*it)->c == SPACE || (*it)->c == LESS
				|| (*it)->c == EPIPE || (*it)->c == GREATER
				|| (*it)->c == SINGLE_QUOTE) && (q % 2 == 0 || q == 0))
			break ;
	}
	return (ptr);
}

char	*get_inside_s_quotes(t_lexer **it)
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
		if (tmp == SINGLE_QUOTE)
			q++;
		*it = advance(*it);
		if (tmp == SINGLE_QUOTE
			&& ((*it)->c == SPACE || (*it)->c == LESS
				|| (*it)->c == EPIPE || (*it)->c == GREATER)
			&& (q % 2 == 0 || q == 0))
			break ;
	}
	return (ptr);
}

char	*check_for_args(t_lexer **lex)
{
	if ((*lex)->c == SINGLE_QUOTE)
		return (get_quote_things(lex));
	else if ((*lex)->c == R_DOUBLE_QUOTE)
		return (get_s_quote_things(lex));
	else
		return (get_s_word(lex));
}

t_arg	*get_args(t_lexer **lex)
{
	char	*s;
	t_arg	*opt;

	opt = NULL;
	while ((*lex)->c)
	{
		if ((*lex)->c == SPACE)
		{
			while ((*lex)->c == SPACE)
				*lex = advance(*lex);
			if ((*lex)->c == EOS)
				return (NULL);
		}
		if ((*lex)->c == EPIPE || (*lex)->c == LESS || (*lex)->c == GREATER)
			break ;
		s = check_for_args(lex);
		if (!s)
			return (NULL);
		if (!opt)
			opt = list_new(s);
		else
			list_add_back(&opt, list_new(s));
		*lex = advance(*lex);
	}
	return (opt);
}

t_token	*get_char(t_lexer **lex)
{
	char	*ptr;
	char	*tmp;

	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	if ((*lex)->c == L_DOUBLE_QUOTE)
		ptr = get_inside_quotes(lex);
	else if ((*lex)->c == SINGLE_QUOTE)
		ptr = get_inside_s_quotes(lex);
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
				if ((*lex)->c == L_DOUBLE_QUOTE)
					tmp = get_inside_quotes(lex);
				else
					tmp = get_inside_s_quotes(lex);
				ptr = ft_strjoin(ptr, tmp);
				free(tmp);
				break ;
			}
		}
	}
	return (init_token(ptr, WORD_CMD, get_args(lex)));
}