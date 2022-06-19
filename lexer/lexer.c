
#include "../includes/minishell.h"

/*
 *exp:
 * 			echo hello
 * 			OR   echo "hel lo"
 * 			OR   ls -la
 * 			OR   ls -l -a
 * 			OR   echo "$HOME" which is variable
 * 			OR	 echo $HOME
 * 			Or 	 echo 'hel lo'  - which print on terminal - hel lo
 * 			OR	  echo '$HOME' 	- which print on terminal - $HOME
 *
 */

// t_token	*get_char(t_lexer **lex)

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

int	generate_token(char *rln_str)
{
	t_token	*token;
	t_lexer	*lexer;
	t_list	*listd_tokn;

	lexer = NULL;
	listd_tokn = NULL;
//	rm_quotes_and_add_space(rln_str);
	lexer = init_lex(lexer, rln_str);
	if (!lexer) {
		return (1);
	}
	while (lexer->i < lexer->str_len)
	{
		token = get_token(lexer);
		printf("content == %s\n", token->content);
		printf("args == %s\n", token->args);
		listd_tokn = priority (listd_tokn, token);
		// free(token);
	}
	listd_tokn = parse_to_tree(listd_tokn);
	// while (listd_tokn)
	// {
	// 	printf("%s\n", listd_tokn->content->content);
	// 	printf("%d\n", listd_tokn->content->child);
	// 	listd_tokn = listd_tokn->next;
	// }
	free(lexer);
	//parse_to_tree(listd_tokn);
	return (EXIT_SUCCESS);
}
