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

void	std_exec(t_list *cmd, char **env)
{
	char	**args;
	char	**path;
	char	*cmand;

	args = arr_arg(cmd);
	if (access(cmd->content->content, X_OK) == 0)
	{
		execve(cmd->content->content, args, env);
	}
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

void	to_std(t_data *exec, char **envp, t_list *cmd)
{
	int	path;

	path = false;
	while (exec->env)
	{
		if (!strncmp(exec->env->pair->key, "PATH", ft_strlen(exec->env->pair->key)))
			path = true;
		exec->env = exec->env->next;
	}
	if (path)
	{
		std_exec(cmd, envp);
	}
	else
		if (printf("~minishell~: %s", cmd->content->content))
			printf(": No such file or directory\n");
}

void	open_pipe(t_data **exec, char mode)
{
	if (mode == 'w')
	{
		if ((*exec)->p_in == 0)
		{
//			fprintf(stderr, "ko in mode 'w'**\n");
			close((*exec)->p_fd[(*exec)->p_in]);
		}
		else
		{
			close((*exec)->p_fd[(*exec)->p_in - 2]);
		}
		if (dup2((*exec)->p_fd[(*exec)->p_in + 1], STDOUT_FILENO) == -1)
		{
			printf("err and should take some work in dup1\n");
		}
	}
	else
	{
//		fprintf(stderr, "ko in mode 'r'**\n");
		close((*exec)->p_fd[(*exec)->p_in - 1]);
//		printf("here  = %d\n", (*exec)->p_in - 2);
		if (dup2((*exec)->p_fd[(*exec)->p_in - 2], STDIN_FILENO) == -1)
		{
			printf("err and should take some work in dup2\n");
		}
	}
}

void	exec_cmd(t_list *cmd, char **envp, t_data *exec)
{
	char	mode;

	if ((exec->cmd_i + 1 != exec->pip_nb + 1))
		mode = 'w';
	else if (exec->cmd_i > 0)
		mode = 'r';
//	if ((exec->cmd_i + 1 != exec->pip_nb + 1) && mode == 'r')
//		if (!isatty(1))
//		{
//			HERE ;
//			dup2(1, exec->p_fd[exec->p_in + 1]);
//		}
	open_pipe(&exec, mode);
	if (!strcmp(cmd->content->content, "echo"))
		echo(cmd);
	else if (!strcmp(cmd->content->content, "env"))
		env_cmd(exec->env);
	else if (!strcmp(cmd->content->content, "cd"))
		cd_cmd(cmd, exec->env);
	else if (!strcmp(cmd->content->content, "pwd")
		|| !strcmp(cmd->content->content, "PWD"))
		pwd_cmd(&exec->env, exec);
	else if (!strcmp(cmd->content->content, "unset"))
	{
		unset_cmd(&exec->env, cmd);
		unset_cmd(&exec->exp, cmd);
	}
	else
		to_std(exec, envp, cmd);
}
