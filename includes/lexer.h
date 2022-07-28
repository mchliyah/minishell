/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:11:46 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/24 22:50:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define WHITESPACE " \t\n\r\v"
# define SYMBOLS " |<>"
# define EOS '\0'
#define SPACE ' '

# include <stdbool.h>

/*
 * 	int (keyword), value (identifier) = e_symbols,
 * 	= (operator), 100 (constant) and ; (symbol).
 */
enum
{
	MINUS = '-',
	EPIPE = '|',
	SINGLE_QUOTE = '\'',
	L_DOUBLE_QUOTE = '\"',
	R_DOUBLE_QUOTE = '\"',
	LESS = '<',
	GREATER = '>',
	ASSIGN = '='
};

typedef struct s_args
{
	enum
	{
		WORD,
		ParameterExpansion
	} e_arg;
	char			*content;
	int				type;
	int				start;
	int				end;
	struct s_args	*next;
	struct s_args	*prev;
}	t_arg;

// ! content is the txt cmd
typedef struct s_token
{
	enum
	{
		Word,
		REDIRECT_IN,
		REDIRECT_OUT,
		DELIMITER,
		REDIRECT_OUT_IN_APPEND_MD,
		PIPE,
		SYNTAX_ERR
	} e_type;
	int		type;
	char	*content;
	t_arg	*arg;

}	t_token;

typedef struct s_lexer
{
	char	c;
	size_t	str_len;
	size_t	i;
	char	*content;
}	t_lexer;

t_token	*init_token(char *str, int type, t_arg *args);
t_lexer	*init_lex(t_lexer *lex, char *rln_str);
char	**ft_split_arg(char const *s, char c);
t_lexer	*advance(t_lexer *lexer);
t_token	*get_char(t_lexer **lex);
int		my_test(t_lexer *lexer);
t_token	*get_token(t_lexer *lexer);
int		get_quote(t_token *token, int *i, int *q);
int		get_s_quote(t_token *token, int *i, int *sq);
t_token	*get_substr_single_quotes(t_token *token);
char	*join_string(char *ptr, char c);
int		get_inside_quote(char const *s, char **str, int i, size_t *k, char c, int j);
int		get_inside_squote(char const *s, char **str, int i, size_t *k, char c, int j);
int		get_words(char const *s, char **str, int i, size_t *k, char c, int j);
bool	check_for_variables(char *str);
char	*get_quote_things(t_lexer **this);
char	*get_s_quote_things(t_lexer **this);
char	*get_s_word(t_lexer **this);
t_arg	*list_new(char	*content);
t_arg	*list_last(t_arg *lst);
void	list_add_back(t_arg **lst, t_arg *new);

#endif