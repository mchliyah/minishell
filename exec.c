/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:25:10 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 21:46:18 by mchliyah         ###   ########.fr       */
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

void	std_exec(t_list *cmd, char **env, int *p_fd, int child)
{
	int		pid;
	char	**args;
	char	**path;
	char	*cmand;

	pid = fork();
	if (pid == 0)
	{
		args = arr_arg(cmd);
		if (access(cmd->content->content, X_OK) == 0)
		{
			execve(cmd->content->content, args, env);
		}
		else
		{
			path = get_cmd_path(env);
			cmand = get_cmd(path, cmd->content->content);
			if (child == 0)
			{
				if (dup2(p_fd[1], STDOUT_FILENO) == -1)
				{
					printf("err and should take some work here");
				}
			}
			else
			{
				if (dup2(p_fd[0], STDIN_FILENO) == -1)
				{
					printf("err and should take some work here");
				}
			}
			execve(cmand, args, env);
		}
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->content->content, 2);
		ft_putstr_fd(" : command not found\n", 2);
	}
	wait(NULL);
}

void	to_std(t_env *env, char **envp, t_list *p_line, int *p_fd, int child)
{
	int	path;

	path = false;
	while (env)
	{
		if (!strncmp(env->pair->key, "PATH", ft_strlen(env->pair->key)))
			path = true;
		env = env->next;
	}
	if (path)
		std_exec(p_line, envp, p_fd, child);
	else
		if (printf("~minishell~: %s", p_line->content->content))
			printf(": No such file or directory\n");
}

void	exec_cmd(t_list *p_line, t_env **env, t_env **exp, char **envp, int child, t_exec *exec)
{
	if ((exec->cmd_n != exec->cmd_size))
	{
		if (dup2(exec->p_fd[exec->p_index + 1], STDOUT_FILENO) == -1)
		{
			printf("err and should take some work in dup\n");
		}
	}
	if (child != 0)
	{
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
		{
			printf("err and should take some work in dup\n");
		}
	}
	if (!strcmp((*p_line).content->content, "echo"))
		echo(p_line);
	else if (!strcmp((*p_line).content->content, "env"))
		env_cmd(*env);
	else if (!strcmp((*p_line).content->content, "cd"))
		cd_cmd(p_line, (*env));
	else if (!strcmp((*p_line).content->content, "pwd")
		|| !strcmp((*p_line).content->content, "PWD"))
		pwd_cmd(env);
	else if (!strcmp((*p_line).content->content, "unset"))
	{
		unset_cmd(env, p_line);
		unset_cmd(exp, p_line);
	}
	else if (!strcmp((*p_line).content->content, "export"))
	{
		// export_cmd(exp, (*p_line)->left);
	}
	else if (!strcmp((*p_line).content->content, "exit"))
	{
		exit_cmd(p_line);
	}
	else
	{
		close(p_fd[1]);
		close(p_fd[0]);
		to_std(*env, envp, p_line, p_fd, child);
	}
//	close(p_fd[1]);
//	close(p_fd[0]);
}
