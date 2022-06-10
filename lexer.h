#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# define WHITESPACE " \t\n\r\v"
# define SYMBOLS "|<>"
/*
 * 	int (keyword), value (identifier) = e_symbols,
 * 	= (operator), 100 (constant) and ; (symbol).
 */
enum
{
	SPACE = ' ',
	SINGLE_QUOTE = '\'',
	L_DOBLE_QUOTE = '\"',
	R_DOBLE_QUOTE = '\"',
	ASSIGN = '='
};

enum
{
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	DELIMITER = '<',
	REDIRECT_OUT_IN_APPEND_MD = '>',
	PIPE = '|'
};

typedef struct s_token
{
	char *token;
	char	*id;
}	t_token;

typedef struct s_lexer
{
	int				token;
	int				index;
	t_token			*t_token;
	struct s_lexer	*next;
}	t_lexer;

int lexer(char *av);
#endif