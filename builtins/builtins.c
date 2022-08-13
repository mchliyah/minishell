/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:26:27 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 21:41:45 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmpair(char *content, char *key)
{
	if (!ft_strcmp(content, key))
		return (0);
	return (1);
}

int	is_builtins(char *content)
{
	if (!cmpair(content, "echo") || !cmpair(content, "ECHO")
		|| !cmpair(content, "env") || !cmpair(content, "ENV")
		|| !cmpair(content, "cd") || !cmpair(content, "CD")
		|| !cmpair(content, "pwd") || !cmpair(content, "PWD")
		|| !cmpair(content, "unset") || !cmpair(content, "export")
		|| !cmpair(content, "exit"))
		return (1);
	return (0);
}

void	buuiltins(char *content, t_list *cmd, t_data **data)
{
	if (!cmpair(content, "echo") || !cmpair(content, "ECHO"))
		echo(cmd);
	else if (!cmpair(content, "env") || !cmpair(content, "ENV"))
		env_cmd((*data)->env);
	else if (!cmpair(content, "cd") || !cmpair(content, "CD"))
		cd_cmd(cmd, (*data)->env);
	else if (!cmpair(content, "pwd") || !cmpair(content, "PWD"))
		pwd_cmd((*data)->env);
	else if (!cmpair(content, "unset"))
	{
		unset_cmd(&(*data)->env, cmd);
		unset_cmd(&(*data)->exp, cmd);
	}
	else if (!cmpair(content, "export"))
		export_cmd(&(*data)->exp, &(*data)->env, cmd);
	else if (!cmpair(content, "exit"))
		(*data)->exit = exit_cmd(cmd);
}
