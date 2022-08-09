/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:07:34 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/02 22:42:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	std_exec(t_list *cmd, char **env)
{
	char	**args;
	char	**path;
	char	*cmand;

	args = arr_arg(cmd);
	if (access(cmd->content->content, X_OK) == 0)
		execve(cmd->content->content, args, env);
	else
	{
		path = get_cmd_path(env);
		cmand = get_cmd(path, cmd->content->content);
		execve(cmand, args, env);
	}
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd->content->content, 2);
	ft_putstr_fd(" : command not found\n", 2);
}

void	to_std(t_env *env, char **envp, t_list *cmd, t_data **data)
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
			std_exec(cmd, envp);
		else if (printf("~minishell~: %s", cmd->content->content))
			printf(": No such file or directory\n");
	}
}
