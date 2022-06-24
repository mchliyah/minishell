
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

//char	*split_by_space(char *s)
//{
//	char	*ptr;
//	char	*t;
//	int	i;
//
//	i = 0;
//	ptr = ft_strdup("");
//	t = malloc(sizeof(char ) * 2);
//	ft_bzero(t, 2);
//	while (s[i])
//	{
//		if (s[i] == SINGLE_QUOTE || s[i] == L_DOBLE_QUOTE)
//		{
//			while (s[i] && s[i] != SINGLE_QUOTE || s[i] != L_DOBLE_QUOTE)
//			{
//				if (s[i] == SPACE)
//				{
//					s[i] = -115;
//				}
//				t[0] = s[i];
//				ptr = ft_strjoin(ptr, t);
//				i++;
//			}
//		}
//		else if (ft_isalpha(s[i]) && ft_strchr(SYMBOLS, s[i+1]))
//		{
//			t[0] = s[i];
//			ptr = ft_strjoin(ptr, t);
//			t[0] = SPACE;
//			ptr = ft_strjoin(ptr, t);
//
//		}
//	}
//}


int	generate_token(char *rln_str)
{
	t_token		*token;
	t_lexer		*lexer;
	t_list		*lst_token;
	// t_pipe_line *pipeline;

	lexer = NULL;
	lst_token = malloc(sizeof(t_list));
//	rm_quotes_and_add_space(rln_str);
	lst_token = NULL;
	lexer = init_lex(lexer, rln_str);
	if (!lexer)
		return (1);
	while (lexer->i < lexer->str_len)
	{
		token = get_token(lexer);
		printf("content == %s\n", token->content);
		// printf("args == %s\n", token->args);
		// lst_token = linked_token(lst_token, token);
		// free(token);
	}
	while(lst_token->next)
	{
		printf("%s\n", lst_token->content->content);
		lst_token = lst_token->next;
	}
	
	// pipeline = parse_to_tree(lst_token);
	// while (pipeline->type == PIPE && pipeline->left_p)
	// {
	// 	while (pipeline->right->next)
	// 	{
	// 		printf("%s\n", pipeline->right->content->content);
	// 		pipeline->right = pipeline->right->next;
	// 	}
	// 	pipeline = pipeline->left_p;
	// }
	//free(lexer);
	//parse_to_tree(listd_tokn);
	return (EXIT_SUCCESS);
}
