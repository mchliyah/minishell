/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:11:46 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/01 19:10:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"
# define WHITESPACE " \t\n\r\v"
# define SYMBOLS " |<>"
# define EOS '\0'

/*
 * 	int (keyword), value (identifier) = e_symbols,
 * 	= (operator), 100 (constant) and ; (symbol).
 */
enum
{
	MINUS = '-',
	M_SPACE = ' ',
	EPIPE = '|',
	SINGLE_QUOTE = '\'',
	L_DOUBLE_QUOTE = '\"',
	R_DOUBLE_QUOTE = '\"',
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
	char	**args;
}	t_token;

typedef struct s_lexer
{
	char	c;
	size_t	str_len;
	size_t	i;
	char	*content;
}	t_lexer;

t_token	*init_token(char *str, int type, char **args);
t_lexer	*init_lex(t_lexer *lex, char *rln_str);
char	**ft_split_arg(char const *s, char c);
t_lexer	*advance(t_lexer *lexer);
t_token	*get_char(t_lexer **lex);
int	my_test(t_lexer *lexer);
t_token	*scan_errs(t_token *token, t_pipe_line *pipe_line);
t_token	*get_token(t_lexer *lexer);
t_token	*get_substr(t_token *token);
int		get_quote(t_token *token, int *i, int *q);
int		get_s_quote(t_token *token, int *i, int *sq);
t_token	*get_substr_single_quotes(t_token *token);
//t_token	*scan_errs(t_token *token);

#endif
