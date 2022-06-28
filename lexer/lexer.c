/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:38 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/27 22:18:54 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


t_token	*get_pipe(t_lexer **lex)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	ft_bzero(str, 2);
	str[0] = (*lex)->c;
	*lex = advance(*lex);
	return (init_token(str, PIPE, NULL));
}

t_token	*get_extra( char *ptr)
{
	if (!ft_strncmp(ptr, "<", ft_strlen(ptr)))
		return (init_token(ptr, REDIRECT_IN, NULL));
	else if (!ft_strncmp(ptr, ">", ft_strlen(ptr)))
		return (init_token(ptr, REDIRECT_OUT, NULL));
	else if (!ft_strncmp(ptr, "<<", ft_strlen(ptr)))
		return (init_token(ptr, DELIMITER, NULL));
	else if (!ft_strncmp(ptr, ">>", ft_strlen(ptr)))
		return (init_token(ptr, REDIRECT_OUT_IN_APPEND_MD, NULL));
	else
		return (init_token(ptr, SYNTAX_ERR, NULL));
}

t_token	*get_redirection(t_lexer **lex)
{
	char	*str;
	char	*ptr;

	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	if ((*lex)->c == SPACE)
		*lex = advance(*lex);
	while ((*lex)->c != '\0' && ((*lex)->c == LESS || (*lex)->c == GREATER))
	{
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
	}
	return (get_extra(ptr));
}

t_token	*get_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == SPACE)
			advance(lexer);
		else if (ft_isalpha(lexer->c) || lexer->c == SINGLE_QUOTE
			|| lexer->c == L_DOBLE_QUOTE)
			return (get_char(&lexer));
		else if (lexer->c == EPIPE)
			return (get_pipe(&lexer));
		else if (lexer->c == LESS | lexer->c == GREATER)
			return (get_redirection(&lexer));
	}
	return (NULL);
}
/*
 ? readline, rl_clear_history, rl_on_new_line,
 ? rl_replace_line, rl_redisplay, add_history,
 ? printf, malloc, free, write, access, open, read,
 ? close, fork, wait, waitpid, wait3, wait4, signal,
 ? sigaction, sigemptyset, sigaddset, kill, exit,
 ? getcwd, chdir, stat, lstat, fstat, unlink, execve,
 ? dup, dup2, pipe, opendir, readdir, closedir,
 ? strerror, perror, isatty, ttyname, ttyslot, ioctl,
 ? getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
 ? tgetnum, tgetstr, tgoto, tputs
 */
int	generate_token(char *rln_str)
{
	t_lexer		*lexer;
	t_list		*lst_token;
	t_pipe_line	*pipeline;

	lexer = NULL;
	lst_token = NULL;
	lexer = init_lex(lexer, rln_str);
	if (!lexer)
		return (1);
	while (lexer->i < lexer->str_len)
			lst_token = linked_token(lst_token, get_token(lexer));
	pipeline = parse_to_tree(lst_token);
	print_tokens(pipeline);
	return (EXIT_SUCCESS);
}
