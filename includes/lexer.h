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

// function deleter of single quote and double quote and expend!
char		*arg_iterator(char *content, t_env *env);

/*
	 * expending functions
 */

void		variable_expander(char **s, t_env *env);
char		*single_quote(char *s, int *i);
char		*h_string_getter(char *s, int i, t_env *env);
/***************************************************/

/*
 *free functions
 */
void		ft_free_token(t_token *token, t_gen_tok var);
void		free_strjoin(char **ptr, char **save);
/*
 * end of free functions
 */

t_gen_tok	generate_init(char *rln_str, t_data **data);
int			cmd_checker(t_lexer **lex);
bool		check_spectial_char(t_lexer **lex);
void		ft_single(t_lexer **lex, char **ptr);
bool		ft_space_advacer(t_lexer **lex);
char		*single_quote_remove(char *s, int *i);
char		*get_s_quote(t_lexer **this);
t_token		*init_token(char *str, int type, t_arg *args);
t_lexer		*init_lex(t_lexer *lex, char *rln_str);
char		*get_form_my_env(char *tmp, t_env *env);
t_lexer		*advance(t_lexer *lexer);
t_token		*get_char(t_lexer **lex, int was_rd);
char		*cmd_getter(t_lexer **lex);
t_token		*get_token(t_lexer **lexer, int first, int was_rd);
void		join_string(char **ptr, char c);
bool		check_for_variables(const char *str);
void		free_parser_data(t_data **data);
char		*get_quote_things(t_lexer **this);
char		*get_s_quote_things(t_lexer **this);
char		*get_s_word(t_lexer **this);
t_arg		*list_new(char	*content);
t_arg		*list_last(t_arg *lst);
void		list_add_back(t_arg **lst, t_arg *new);
void		get_last(char *s, int *i);
int			syntax_err_checker(t_list *token);

#endif