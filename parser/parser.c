/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:55:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/19 23:04:06 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
t_fdinout	*open_fds(t_list	*lst_t, t_fdinout	*fds)
{
	fds->i = 0;
	fds->j = 0;
	while (lst_t)
	{
		if (lst_t->content->type == REDIRECT_IN)
			fds->fdin[fds->i++] = open(lst_t->next->content->content, O_RDONLY);
		else if (lst_t->content->type == REDIRECT_OUT)
			fds->fdout[fds->j++] = open(lst_t->next->content->content, O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
		lst_t = lst_t->next;
	}
	return (fds);
}

t_fdinout	*init_fds(t_list	*lst_tok, t_fdinout	*fds)
{
	t_list	*tmp;
	int k;
	int l;

	fds->i = 0;
	fds->j = 0;
	tmp = lst_tok;
	while (tmp)
	{
		if (tmp->content->type == REDIRECT_IN)
			fds->i++;
		else if (tmp->content->type == REDIRECT_OUT)
			fds->j++;
		tmp = tmp->next;
	}
	if (fds->i)
		fds->fdin = malloc(sizeof(int *) * fds->i);
	if (fds->j)
	fds->fdout = malloc(sizeof(int *) * fds->j);
	// free_list(tmp);
	k = fds->i;
	l = fds->j;
	fds = open_fds(lst_tok, fds);
	if (k)
	{
		while (k >= 0)
		{
			printf("fd in arr %d\n", fds->fdin[k]);
			k--;
		}
	}
	return (fds);
}

void	add_childs_id(t_list *lst_token, int i)
{
	if (lst_token->content->type == PIPE)
	{
		lst_token->content->child = -1;
		lst_token = lst_token->next;
	}
	while (lst_token && lst_token->content->type != PIPE)
	{
		lst_token->content->child = i;
		lst_token = lst_token->next;
	}
}
// will return a parsed tree
t_list	*parse_to_tree(t_list *lst_token)
{
	int			i;
	t_fdinout	*fds;
	t_list		*tmp;

	i = 0;
	fds = malloc(sizeof(t_fdinout));
	fds = init_fds(lst_token, fds);
	while (lst_token)
	{
		if (lst_token->content->type == REDIRECT_IN
			|| lst_token->content->type == REDIRECT_OUT)
		{
			tmp = lst_token;
			lst_token->next = lst_token->next->next;
			lst_token->next->next->prev = tmp;
		}
		lst_token = lst_token->next;
	}
	while (lst_token->prev)
	{
		if (lst_token->content->type == PIPE)
			add_childs_id(lst_token, i++);
		lst_token = lst_token->prev;
	}
	add_childs_id(lst_token, i);
	return (lst_token);
}
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
