/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/18 22:26:57 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int			generate_token(char *rln_str, t_p_line **pipeline, t_data **data);
t_p_line	*to_pipe(t_list *lst_token, t_p_line	**pipeline, int frst_p);
t_list		*linked_token(t_list	*lst_token, t_token *token);
int			pipe_exist(t_list *lst);
void		error_check(t_list *lst_token);
t_list		*copy_list(t_list *ret, t_list *to_copy);
// those function from lexer
bool        scan_errs(t_token **token, t_env *env, int was_rd);
t_arg		*remove_quoted_args(t_arg *token, t_env *env);
char		*get_variable(char *arg, t_env *env, int state);
int			scan_args(t_arg **token, t_env *env);
char		*get_simple_word(char *arg, t_env *env, int state);
t_token		*scan_vars(t_token *token, t_env *env, int was_hered);
t_token		*get_substr(t_token *token, t_env *env);
char		*rm_quote(char *arg, t_env *env, int state);
//end

#endif
