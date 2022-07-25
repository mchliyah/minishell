/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/25 03:26:07 by mchliyah         ###   ########.fr       */
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

char	**arr_arg(t_list *cmd)
{
	char	**args;
	t_arg	*track;
	t_arg	*track1;
	int		i;

	i = 0;
	track = cmd->content->arg;
	while (track)
	{
		track = track->next;
		i++;
	}
	args = malloc(sizeof(char *) * (i + 2));
	args[0] = cmd->content->content;
	i = 1;
	track1 = cmd->content->arg;
	while (track1)
	{
		args[i++] = track1->content;
		track1 = track1->next;
	}
	args[i] = NULL;
	return (args);
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
	waitpid(pid, 0, 0);
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

void	exec_cmd(t_pipe_line *p_line, t_env *env, char **envp)
{
	char	**args;

	(void)env;
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
	{
		args = arr_arg(p_line->left);
		env = unset_cmd(env, args);
	}
	else if (!strcmp(p_line->left->content->content, "export"))
		printf("dzt mn han :)\n");
	else if (!strcmp(p_line->left->content->content, "exit"))
		exit_cmd(p_line);
	else
	{
		if (!check_path(env, "PATH"))
			std_exec(p_line->left, envp);
		else
			printf("~minishell~: %s: No such file or directory\n", p_line->left->content->content);
	}
}
