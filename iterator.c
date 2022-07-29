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


int	iterator(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp)
{
	int	ret_pipe;
	int	p_fd[2];

	if (this_pipe->left_p)
	{
		iterator(this_pipe->left_p, env, exp, envp);
	}
	ret_pipe = pipe(p_fd);
	if (ret_pipe == -1)
		return (EXIT_FAILURE);
	if (this_pipe->left)
	{
		printf("left == %s\n", this_pipe->left->content->content);
	}
	if (this_pipe->right)
		printf("right == %s\n", this_pipe->right->content->content);
	return (EXIT_SUCCESS);
}