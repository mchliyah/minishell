#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>

enum
{
	SPACE = ' ',
	SINGLE_QUOTE = '\'',
	DOBLE_QUOTE = '\"',
}	e_separators;

enum
{
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	DELIMITER = "<<",
	REDIRECT_OUT_IN_APPEND_MD = ">>",
	PIPES = "|"
}	e_symbols;

typedef struct s_token
{
	char *token;
}	t_token;

typedef struct s_lexer
{
	int		token;
	int		index;
	char	*id;
	s_token	*t_token;
}	t_lexer;

int lexer(char **av);
#endif