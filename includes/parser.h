/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:51 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/17 17:04:40 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

 typedef struct s_pipeline
 {
	 char				*type;
	 struct s_pipeline	*left;
	 struct s_pipeline	*right;
 } t_pipe_line;

 typedef struct s_cmd_word
 {
	 char	*type;
	 char	*arg;
 } t_cmd_word;

typedef struct s_redirection
{
	char	*type;
	struct s_redirection *next;
}	t_redirection;

//typedef struct s_files
//{
//	char	*type;
//	int		fd;
//	struct s_redirection *next;
//} t_pipeline;

t_list	*parse_to_tree(t_list *lst_token);
t_list	*priority(t_list	*lst_token, t_token *token);

#endif