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
	MINUS = '-',
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
// ! id_type exp: word like ls or < less or << d_less and so on
// ! content is the txt cmd
typedef struct s_token
{
	char	*content;
	char	*id_type;
}	t_token;
// ! type exp : pipeline or command or prefix or suffix
typedef struct s_lexer
{
	char			*type;
	t_token			*token;
	struct s_lexer	*next;
}	t_lexer;

int lexer(char *av);
#endif