/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:48:21 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/10 19:58:09 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*scan_vars(t_token *token, t_env *env, int was_hered)
{
	char	c;
	char	**ptr;
	if (was_hered == 2)
	{
		if ()
		ptr = ft_split()
		token->content = ft_split();
	}
	else
    	token->content = arg_iterator(token->content, env);
	return (token);
}
