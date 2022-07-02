/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/02 17:02:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_pipe_line *p_line)
{
	if (!strcmp(p_line->left->content->content, "echo"))
		echo(p_line->left);
	else if (!strcmp(p_line->left->content->content, "env"))
		env_cmd(p_line);
	else if (!strcmp(p_line->left->content->content, "cd"))
		p_line->env = cd_cmd(p_line->left, p_line->env);
}
