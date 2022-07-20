/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/19 14:16:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	std_exec(t_pipe_line *p_line, t_env *env)
{
	(void)p_line;
	(void)env;
	printf("cmd -> %s\n", p_line->left->content->content);
	printf("std exec reached\n");
	// if (access(p_line->left->content->content, X_OK) == 0)
	// 	execve(p_line->left->content->content, &p_line->left->content->args[0], env);
}

void	exec_cmd(t_pipe_line *p_line, t_env *env)
{
	(void)env;
	g_status = 1;
	if (!strcmp(p_line->left->content->content, "echo"))
		echo(p_line->left);
	else if (!strcmp(p_line->left->content->content, "env"))
		env_cmd(env);
	else if (!strcmp(p_line->left->content->content, "cd"))
		cd_cmd(p_line->left, env);
	else if (!strcmp(p_line->left->content->content, "pwd")
		|| !strcmp(p_line->left->content->content, "PWD"))
		pwd_cmd(env);
	else if (!strcmp(p_line->left->content->content, "unset"))
		printf("dzt mn han :)\n");
	else if (!strcmp(p_line->left->content->content, "export"))
		printf("dzt mn han :)\n");
	else if (!strcmp(p_line->left->content->content, "exit"))
		exit_cmd(p_line);
	else
		std_exec(p_line, env);
}
