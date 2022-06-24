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

/*
  		TODO : - do something
			    - dead line = 24 next month
 */

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

//char	*quoted_arg(t_lexer **this)
//{
//
//}
//size_t	count_arg(t_lexer *lex)
//{
//	size_t	cnt;
//	t_lexer	*this;
//
//	this = lex;
//	cnt = 0;
//	while (this->c != EOS)
//	{
//		if ((this->c == EPIPE || this->c == LESS || this->c == GREATER)
//			&& (nbq == 0 || nbq % 2 == 0))
//			break ;
//		else if (this->c == SINGLE_QUOTE || this->c == L_DOBLE_QUOTE)
//		this = advance(this);
//	}
//}
//char	**check_for_args(t_lexer **this, int i)
//{
//	int 	j;
//	char	**ptr;
//	char	h;
//	char	*str;
//
//	ptr = NULL;
//	j = 0;
//	while ((*this)->c == SPACE)
//		*this = advance(*this);
//	if ((*this)->c == EPIPE || (*this)->c == LESS
//		|| (*this)->c == GREATER || (*this)->c == '\0')
//		return (NULL);
//	if ((*this)->c == SINGLE_QUOTE || (*this)->c == L_DOBLE_QUOTE)
//		quoted_arg(*this)
//	while ((*this)->c != '\0')
//	{
//		ptr[j] = ft_strdup("");
//		h = (*this)->c;
//		*this = advance(*this);
//		j++;
//	}
//	return (ptr);
//}

/*
 *   -------------------------------------
 * 	 function for member of get_char() !!
 * 	 -----------------------------------
  	 !  "ls""| pwd  should be fixed
 */
char	*get_inside_quotes(t_lexer **it)
{
	char	tmp;
	char	*ptr;

	ptr = NULL;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while ((*it)->c != '\0')
	{
		ptr = join_string(ptr, (*it)->c);
		tmp = (*it)->c;
		*it = advance(*it);
		if ((tmp == SINGLE_QUOTE || tmp == L_DOBLE_QUOTE)
			&& ((*it)->c == SPACE || (*it)->c == LESS
				|| (*it)->c == EPIPE || (*it)->c == GREATER))
			break ;
	}
	return (ptr);
}

t_token	*get_char(t_lexer **lex)
{
	int		i;
	char	*ptr;
	char	*str;
	char	*tmp;
//	char **args = NULL;
	i = 0;
	str = NULL;
	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
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
			else if (((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
				&& (*lex)->c != '0')
			{
				tmp = get_inside_quotes(lex);
				ptr = ft_strjoin(ptr, tmp);
				free(tmp);
				break ;
			}
		}
	}
	//str = check_for_args(lex, i);
	return (init_token(ptr, WORD, str));
}