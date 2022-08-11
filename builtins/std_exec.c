/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:07:34 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/11 00:57:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	std_exec(t_list *cmd, t_env *env)
{
	char	**args;
	char	**path;
	char	*cmand;
	char	**envp;

	args = arr_arg(cmd);
	envp = get_env_char(env);
	if (access(cmd->content->content, X_OK) == 0)
		execve(cmd->content->content, args, envp);
	else
	{
		path = get_cmd_path(envp);
		cmand = get_cmd(path, cmd->content->content);
		execve(cmand, args, envp);
	}
	if (access(cmd->content->content, _OK) == 0)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->content->content, 2);
	}
	ft_putstr_fd(" : command not found\n", 2);
	exit(127);
}

void	to_std(t_env *env, t_list *cmd, t_data **data)
{
	int	f_pid;
	int	path;

	f_pid = 0;
	if ((*data)->pip_nb == 0)
		f_pid = fork();
	if (f_pid == -1)
	{
		perror("fork(): ");
		exit(1);
	}
	if (f_pid == 0)
	{
		path = false;
		while (env)
		{
			if (!strncmp(env->pair->key, "PATH", ft_strlen(env->pair->key)))
				path = true;
			env = env->next;
		}
		if (path)
			std_exec(cmd, (*data)->env);
		else if (printf("~minishell~: %s", cmd->content->content))
			printf(": No such file or directory\n");
	}
}
