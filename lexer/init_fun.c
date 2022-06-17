#include	"../includes/minishell.h"

t_token	*init_token(char *str, int type, char *args)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = str;
	token->args = args;
	return (token);
}

t_lexer	*init_lex(t_lexer *lex, char *rln_str)
{
	lex = malloc(sizeof(t_lexer));
	lex->content = rln_str;
	lex->i = 0;
	lex->str_len = ft_strlen(rln_str);
	lex->c = lex->content[lex->i];
	return (lex);
}
