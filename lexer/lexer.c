/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:38 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/12 03:13:07 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

t_token	*get_pipe(t_lexer **lex, int first)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		exit(g_status);
	while ((*lex)->c)
	{
		if ((*lex)->c != EPIPE)
			break ;
		join_string(&str, (*lex)->c);
		*lex = advance(*lex);
		while ((*lex)->c == SPACE)
			*lex = advance(*lex);
	}
	if (!ft_memcmp(str, "|", ft_strlen(str)) && first == 0)
		return (init_token(str, PIPE, NULL));
	return (init_token(str, SYNTAX_ERR, NULL));
}

t_token	*get_extra( char *ptr)
{
	if (!ft_strcmp(ptr, "<"))
		return (init_token(ptr, REDIRECT_IN, NULL));
	else if (!ft_strcmp(ptr, ">"))
		return (init_token(ptr, REDIRECT_OUT, NULL));
	else if (!ft_strcmp(ptr, "<>"))
		return (init_token(ptr, LESSGREAT, NULL));
	else if (!ft_strcmp(ptr, "<<"))
		return (init_token(ptr, DELIMITER, NULL));
	else if (!ft_strcmp(ptr, ">>"))
		return (init_token(ptr, REDIRECT_OUT_IN_APPEND_MD, NULL));
	else
		return (init_token(ptr, SYNTAX_ERR, NULL));
}

void	get_redirection_helper(char **ptr, t_lexer **lex)
{
	char	*tmp;
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
	{
		perror("malloc");
		exit(1);
	}
	ft_bzero(str, 2);
	str[0] = (*lex)->c;
	tmp = ft_strjoin(*ptr, str);
	if (!tmp)
	{
		perror("malloc");
		exit(1);
	}
	free_strjoin(ptr, &str);
	*ptr = tmp;
	*lex = advance(*lex);
}

t_token	*get_redirection(t_lexer **lex)
{
	char	*ptr;

	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	while ((*lex)->c != '\0' && ((*lex)->c == LESS || (*lex)->c == GREATER))
		get_redirection_helper(&ptr, lex);
	while ((*lex)->c == SPACE)
		*lex = advance(*lex);
	return (get_extra(ptr));
}

t_token	*get_token(t_lexer **lexer, int first, int was_rd)
{
	while ((*lexer)->c != '\0')
	{
		while ((*lexer)->c == SPACE)
			*lexer = advance(*lexer);
		if (ft_isprint((*lexer)->c) && (*lexer)->c != EPIPE
			&& (*lexer)->c != GREATER && (*lexer)->c != LESS)
			return (get_char(lexer, was_rd));
		else if ((*lexer)->c == LESS || (*lexer)->c == GREATER)
			return (get_redirection(lexer));
		else if ((*lexer)->c == EPIPE)
			return (get_pipe(lexer, first));
	}
	return (NULL);
}
