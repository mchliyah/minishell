/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:07:34 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 22:41:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

char	**get_env_char(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		size;
	int		i;

	size = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * size + 1);
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->pair->key);
		arr[i] = ft_strjoin(arr[i], "=");
		arr[i] = ft_strjoin(arr[i], tmp->pair->value);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

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

	while (ft_strncmp("PATH=", *env, 5))
	{
		if (ft_strncmp("PATH=", *env, 5) == -1)
			ft_putstr_fd("err cmand \n", 2);
		env++;
	}
	path = ft_split(*env + 5, ':');
	return (path);
}

void	std_exec(t_list *cmd, t_data **data, char **envp, char **args)
{
	char	**path;
	char	*cmand;
	t_env	*env;

	env = (*data)->env;
	if (access(cmd->content->content, X_OK) == 0)
		execve(cmd->content->content, args, envp);
	else
	{
		path = get_cmd_path(envp);
		cmand = get_cmd(path, cmd->content->content);
		execve(cmand, args, envp);
	}
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd->content->content, 2);
	if (getcwd(cmd->content->content, ft_strlen(cmd->content->content)) != 0)
		perror(cmd->content->content);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	to_std(t_list *cmd, t_data **data)
{
	int		path;
	char	**envp;
	char	**args;
	// int		pid;
	t_env	*env;

	env = (*data)->env;
	envp = get_env_char(env);
	args = arr_arg(cmd);
	signal(SIGINT, SIG_DFL);
	path = false;
	while (env)
	{
		if (!strcmp(env->pair->key, "PATH"))
			path = true;
		env = env->next;
	}
	if (path)
		std_exec(cmd, data, envp, args);
	else
	{
		if (access(cmd->content->content, X_OK) == 0)
			execve(cmd->content->content, args, envp);
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->content->content, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(127);
}
