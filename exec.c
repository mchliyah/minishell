/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/02 18:30:00 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cmpair(char *content, char *key)
{
	if (!ft_strncmp(content, key, ft_strlen(content)))
		return (0);
	return (1);
}

void	exec_cmd(t_list *cmd, t_env **env, t_env **exp, char **envp)
{
	char	*content;

	content = cmd->content->content;
	if (!cmpair(content, "echo") || !cmpair(content, "ECHO"))
		echo(cmd);
	else if (!cmpair(content, "env") || !cmpair(content, "ENV"))
		env_cmd(*env);
	else if (!cmpair(content, "cd") || !cmpair(content, "CD"))
		cd_cmd(cmd, (*env));
	else if (!cmpair(content, "pwd") || !cmpair(content, "PWD"))
		pwd_cmd(env);
	else if (!cmpair(content, "unset"))
	{
		unset_cmd(env, cmd);
		unset_cmd(exp, cmd);
	}
	else if (!cmpair(content, "export"))
		export_cmd(exp, env, cmd);
	else if (!cmpair(content, "exit"))
		exit_cmd(cmd);
	else
		to_std(*env, envp, cmd);
}
