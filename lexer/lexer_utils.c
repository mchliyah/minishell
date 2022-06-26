/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:50:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/26 19:44:42 by mchliyah         ###   ########.fr       */
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
char	has_next(t_lexer *it)
{
	t_lexer	*this;

	this = it;
	this->i++;
	this->c = this->content[this->i];
	return (this->c);
}
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
		if ((*lex)->c == SINGLE_QUOTE || (*lex)->c == L_DOBLE_QUOTE)
			q++;
		else if (((*lex)->c == EPIPE || (*lex)->c == LESS
				|| (*lex)->c == GREATER || (*lex)->c == '\0')
			&& (q == 0 || q % 2 == 0))
		{
			end = (*lex)->i;
			break ;
		}
		*lex = advance(*lex);
		if ((*lex)->c == EOS)
		{
			end = (*lex)->i;
			break ;
		}
	}
	str = ft_substr((*lex)->content, start, end - start);
	return (ft_split_arg(str, ' '));
}

t_token	*get_char(t_lexer **lex)
{
	int		i;
	int		k;
	char	*ptr;
	char	**str;
	char	*tmp;

	i = 0;
	k = 0;
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
//	if (i%2 == 1)
//	{
//		printf("cmd %s   err %c\n", ptr, L_DOBLE_QUOTE);
//		exit(0);
//	}
	// str = check_for_args(lex);
	// str = check_for_args(lex, i);
	//check_for_args(lex, i);
	//str = check_for_args(lex, i);
	// return (init_token(ptr, WORD, str));
	str = check_for_args(lex);
	while (str[k])
	{
		printf("arg[%d] %s \n",k, str[k]);
		k++;
	}
	return (init_token(ptr, WORD, NULL));
}