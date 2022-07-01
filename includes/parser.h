/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/01 14:13:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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
}	t_pipeline;

t_pipe_line	*parse_to_tree(t_list *lst_token);
t_list		*linked_token(t_list	*lst_token, t_token *token);
int			pipe_exist(t_list *lst);
void		error_check(t_list *lst_token);
void		free_lst(t_list *list);

#endif