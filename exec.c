/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/25 19:04:16 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

char	**get_cmd_path(char **env)
{
	char	**path;

	while (ft_strncmp("PATH=", *env, 4))
	{
		if (ft_strncmp("PATH=", *env, 4) == -1)
			PV("err cmand \n", "%s");
		env++;
	}
	path = ft_split(*env + 5, ':');
	return (path);
}

void	std_exec(t_list *cmd, char **env)
{
	int		pid;
	char	**args;
	char	**path;
	char	*cmand;

	pid = fork();
	if (pid == 0)
	{
		if (access(cmd->content->content, X_OK) == 0)
		{
			args = arr_arg(cmd);
			execve(cmd->content->content, args, env);
		}
		else
		{
			path = get_cmd_path(env);
			cmand = get_cmd(path, cmd->content->content);
			args = arr_arg(cmd);
			execve(cmand, args, env);
		}
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->content->content, 2);
		ft_putstr_fd(" : command not found\n", 2);
	}
	wait(NULL);
}

int	check_path(t_env *env, char *key)
{
	while (env)
	{
		if (!strncmp(env->pair->key, key, ft_strlen(key)))
			return (0);
		env = env->next;
	}
	return (1);
}

void	exec_cmd(t_pipe_line *p_line, t_env *env, t_env *exp, char **envp)
{
	(void)exp;
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
		env = unset_cmd(env, p_line->left);
	else if (!strcmp(p_line->left->content->content, "export"))
		printf("dzt mn han :)\n");
	else if (!strcmp(p_line->left->content->content, "exit"))
		exit_cmd(p_line);
	else
	{
		if (!check_path(env, "PATH"))
			std_exec(p_line->left, envp);
		else
			printf("~minishell~: %s: No such file or directory\n",
				p_line->left->content->content);
	}
}
