/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/02 20:45:18 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_cmd(t_pipe_line *p_line)
{
	t_env	*env;

	if (!strcmp(p_line->left->content->content, "echo"))
		echo(p_line->left);
	else if (!strcmp(p_line->left->content->content, "env"))
		env_cmd(p_line);
	else if (!strcmp(p_line->left->content->content, "cd"))
	{
		p_line->env = cd_cmd(p_line->left, p_line->env);
		env = p_line->env;
		while (env)
		{
			printf("%s\n", env->value);
			env = env->next;
		}
	}
	else if (!strcmp(p_line->left->content->content, "pwd")
		|| !strcmp(p_line->left->content->content, "PWD"))
		pwd_cmd(p_line);
}
