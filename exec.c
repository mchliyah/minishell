/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/04 17:01:45 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	std_exec(t_pipe_line *p_line, char **env)
// {
// 	printf("i got here\n");
// 	if (access(p_line->left->content->content, X_OK) == 0)
// 		execve(p_line->left->content->content, &p_line->left->content->args[0], env);
// }

void	exec_cmd(t_pipe_line *p_line, char **env)
{
	(void)env;
	if (!strcmp(p_line->left->content->content, "echo"))
		echo(p_line->left);
	else if (!strcmp(p_line->left->content->content, "env"))
		env_cmd(p_line);
	else if (!strcmp(p_line->left->content->content, "cd"))
		cd_cmd(p_line->left, p_line->env);
	else if (!strcmp(p_line->left->content->content, "pwd")
		|| !strcmp(p_line->left->content->content, "PWD"))
		pwd_cmd(p_line);
	// else
	// 	std_exec(p_line, env);
}
