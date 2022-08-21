/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_holder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:39:50 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 10:39:55 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	simple_cmd(t_p_line **pipeline, t_list *lst_token)
{
	t_list	*tmp;

	tmp = lst_token;
	(*pipeline)->type = WORD;
	(*pipeline)->right = NULL;
	(*pipeline)->left = NULL;
	(*pipeline)->left_p = NULL;
	(*pipeline)->left = copy_list((*pipeline)->left, tmp);
}

t_p_line	*to_tree(t_p_line **pipeline, t_list *lst_token, t_data **data)
{
	int			frst_pipe;

	frst_pipe = 1;
	(*data)->pip_nb = pipe_exist(lst_token);
	if ((*data)->pip_nb)
	{
		while (lst_token)
		{
			if (lst_token->content->type == PIPE)
			{
				*pipeline = to_pipe(lst_token, pipeline, frst_pipe);
				frst_pipe = 0;
			}
			lst_token = lst_token->next;
		}
	}
	else
		simple_cmd(pipeline, lst_token);
	return (*pipeline);
}

int	check_token(t_token **token, t_data **data, int was_rd)
{
	if (!scan_errs(token, (*data)->env, was_rd))
		return (0);
	return (2);
}
