/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/04 01:29:58 by mchliyah         ###   ########.fr       */
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
	t_env				*env;
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

t_pipe_line	*parse_to_tree(t_pipe_line *pipeline, t_list *lst_token);
t_list		*linked_token(t_list	*lst_token, t_token *token);
int			pipe_exist(t_list *lst);
void		error_check(t_list *lst_token);
void		free_lst(t_list *list);
t_token		*scan_errs(t_token *token, t_pipe_line *pipe_line);
t_token		*remove_quoted_args(t_token *token, t_pipe_line *pipe_line);
char		*get_variable(char *arg, t_pipe_line *pipe_line);

#endif
