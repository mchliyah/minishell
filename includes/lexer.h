/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:11:46 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/19 20:45:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# define WHITESPACE " \t\n\r\v"
# define SYMBOLS " |<>"
/*
 * 	int (keyword), value (identifier) = e_symbols,
 * 	= (operator), 100 (constant) and ; (symbol).
 */
enum
{
	MINUS = '-',
	SPACE = ' ',
	EPIPE = '|',
	SINGLE_QUOTE = '\'',
	L_DOBLE_QUOTE = '\"',
	R_DOBLE_QUOTE = '\"',
	LESS = '<',
	GREATER = '>',
	ASSIGN = '='
};

// ! content is the txt cmd
typedef struct s_token
{
	enum
	{
		WORD,
		REDIRECT_IN,
		REDIRECT_OUT,
		DELIMITER,
		REDIRECT_OUT_IN_APPEND_MD,
		PIPE,
		SYNTAX_ERR
	} e_type;

	int		type;
	char	*content;
	char	*args;
	int		child;
}	t_token;

typedef struct s_lexer
{
	char	c;
	size_t	str_len;
	size_t	i;
	char	*content;
}	t_lexer;

t_token	*init_token(char *str, int type, char *args);
t_lexer	*init_lex(t_lexer *lex, char *rln_str);
int		generate_token(char *av);
t_lexer	*advance(t_lexer *lexer);
int		generate_token(char *av);
t_token	*get_char(t_lexer **lex);
#endif
