/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/17 22:27:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_list	*priority(t_list	*lst_token, t_token *token)
{
	if (!lst_token)
		lst_token = ft_lstnew(token);
	else
		ft_lstadd_back(&lst_token, ft_lstnew(token));
	return (lst_token);
}
// ! if we have a PIPE
//t_pipe_line	*pipe_line(t_list *token)
//{
//
//}

//    // will return a parsed tree
//t_list *parse_to_tree(t_list *lst_token)
//{
//	t_pipe_line	*pipe;
//	t_list		*token_tmp;
//
//	token_tmp = lst_token;
//	pipe = malloc(sizeof(t_pipe_line));

//	while (token_tmp)
//	{
//		if (token_tmp->content->type == PIPE)
//			pipe_line(token_tmp);
//		if (token_tmp->content->type == WORD)
//			simple_cmd();
//		if (token_tmp->content->type == REDIRECT_IN || token_tmp->content->type == REDIRECT_OUT)
//			redirect_in_out();
//		if (token_tmp->content->type == DELIMITER)
//			get_delimiter();
//		if (token_tmp->content->type == REDIRECT_OUT_IN_APPEND_MD)
//			redirict_out_in_append();
//		if (token_tmp->content->type == SYNTAX_ERR)
//		{
//			printf("there is an err in syntax\n");
//			exit(EXIT_FAILURE);
//		}
//		token_tmp = token_tmp->next;
//	}
//}