/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:57:21 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 12:42:38 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*
 * int			*p_fd; // for pipe FILE_DESCRIPTORS
 *	int			cmd_n; // index of the command in its order
 *	int			cmd_size; // COMMAND NUMBER FOR CHECKING THE LAST CMD
 */
typedef struct s_exec
{
	int			*p_fd;
	int			cmd_n;
	int			cmd_size;
	int			p_index;
}	t_exec;

void	exec_cmd(t_list *c_line, t_env **env, t_env **exp, char **envp, int *p_fd, int child, int cmd_n);
char	*get_path(char *path, t_env *env);
void	echo(t_list *cmd);
void	env_cmd(t_env *env);
void	cd_cmd(t_list	*c_line, t_env *env);
void	pwd_cmd(t_env **env);
void	exit_cmd(t_list *p_line);
void	unset_cmd(t_env **env, t_list *cmd);
char	**arr_arg(t_list *cmd);
t_env	*start(char **envp);
t_pair	*init_pair(char *tmp_val);
void	export_cmd(t_env **exp, t_list *c_line);
int		iterator(t_pipe_line *this_pipe, t_env **env, t_env **exp, char **envp, t_exec *exec);

#endif
