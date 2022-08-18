/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:11:46 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/04 00:23:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structs.h"
# include "minishell.h"

/*
 * 	int (keyword), value (identifier) = e_symbols,
 * 	= (operator), 100 (constant) and ; (symbol).
 */

// function deleter of single quote and double quote and expend!
char	*arg_iterator(char *content, t_env *env);

/*
	 * expending functions
 */

char	*variable_expander(char *s, t_env *env);
char	*single_quote(char *s, int *i);
char	*h_string_getter(char *s, int i, t_env *env);
/***************************************************/

void	free_lexer_var(t_gen_tok var);
t_token	*init_token(char *str, int type, t_arg *args);
t_lexer	*init_lex(t_lexer *lex, char *rln_str);
char	*get_form_my_env(char *tmp, t_env *env);
t_lexer	*advance(t_lexer *lexer);
t_token	*get_char(t_lexer **lex, int was_rd);
char	*cmd_getter(t_lexer **lex);
t_token	*get_token(t_lexer **lexer, int first, int was_rd);
void	join_string(char **ptr, char c);
bool	check_for_variables(const char *str);
char	*get_quote_things(t_lexer **this);
char	*get_s_quote_things(t_lexer **this);
char	*get_s_word(t_lexer **this);
t_arg	*list_new(char	*content);
t_arg	*list_last(t_arg *lst);
void	list_add_back(t_arg **lst, t_arg *new);
int		check_gaven_file_rd(t_list *token);
void	free_parser_data(t_data **data);

int		get_inside_quote(char const *s, char **str, int i, size_t *k, char c, int j);
int		get_inside_squote(char const *s, char **str, int i, size_t *k, char c, int j);
int		get_words(char const *s, char **str, int i, size_t *k, char c, int j);
int		expend(char **ptr, char *arg, t_env *env);
char	*double_quote(char *s, int *i, t_env *env);
t_token	*get_token_file(t_lexer **lex);
//char	**ft_split_arg(char const *s, char c);
//int		my_test(t_lexer *lexer);
//int		get_quote(t_token *token, int *i, int *q);
//int		get_s_quote(t_token *token, int *i, int *sq);
//t_token	*get_substr_single_quotes(t_token *token);

#endif