/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:59:16 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/19 22:05:13 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parser_data(t_data **data)
{
	free((*data)->p_fd);
}

void	ft_free_token(t_token *token, t_gen_tok var)
{
	if (token->content)
	{
		while (token->arg)
		{
			free(token->arg->content);
			free(token->arg);
			token->arg = token->arg->next;
		}
		free(token->content);
	}
	free(token);
	free(var.lexer);
}

void	free_strjoin(char **ptr, char **save)
{
	free(*ptr);
	free(*save);
	*ptr = NULL;
	*save = NULL;
}
