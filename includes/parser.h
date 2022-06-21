/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/22 00:34:25 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd_word
{
	char	*type;
	char	*arg;
}	t_cmd_word;

typedef struct s_pipeline
{
	int					type;
	struct s_pipeline	*left;
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
void		free_lst(t_list *list);

#endif