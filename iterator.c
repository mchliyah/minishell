/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/27 19:57:27 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


int	iterator(t_pipe_line **pipeline, t_env **env, t_env **exp, char **envp)
{
	t_pipe_line	*this_pipe;
	t_pipe_line	*head;

	this_pipe = *pipeline;
	if (this_pipe->left_p)
		return (iterator(this_pipe->left_p, envm exp, envp));
	return (EXIT_SUCCESS);
}