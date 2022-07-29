/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 11:44:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "../libft/libft.h"

typedef struct s_pair
{
	char			*key;
	char			*value;
}	t_pair;

typedef struct s_env
{
	struct s_pair	*pair;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd_word
{
	char	*type;
	char	*arg;
}	t_cmd_word;

typedef struct s_pipeline
{
	int					exit;
	int					type;
	struct s_pipeline	*left_p;
	t_list				*left;
	t_list				*right;
}	t_pipe_line;

typedef struct s_redirection
{
	char					*type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_files
{
	char					*type;
	int						fd;
	struct s_redirection	*next;
}	t_files;

void		parse_to_tree(t_pipe_line **pipeline, t_list *lst_token);
t_list		*linked_token(t_list	*lst_token, t_token *token);
int			pipe_exist(t_list *lst);
void		error_check(t_list *lst_token);
void		free_lst(t_list *list);
// those function from lexer
t_token		*scan_errs(t_token *token, t_env *env);
t_arg		*remove_quoted_args(t_arg *token, t_env *env);
char		*get_variable(char *arg, t_env *env, int state);
t_arg		*scan_args(t_arg *token, t_env *env);
char		*get_simple_word(char *arg, t_env *env, int state);
t_token		*scan_vars(t_token *token, t_env *env);
t_token		*get_substr(t_token *token, t_env *env);
char		*rm_quote(char *arg, t_env *env, int state);
//end

#endif
