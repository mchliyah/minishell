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
# include "minishell.h"

//char	*get_path(char *path, t_env *env);

void	env_cmd(t_env *env);
void	cd_cmd(t_list	*c_line, t_env *env);
//void	pwd_cmd(t_env **env, t_data *exec);
void	exit_cmd(t_pipe_line **p_line);
void	unset_cmd(t_env **env, t_list *cmd);
char	**arr_arg(t_list *cmd);
t_env	*start(char **envp);
t_pair	*init_pair(char *tmp_val);
void	export_cmd(t_env **exp, t_list *c_line);
t_env	*update_path(t_env *env, char *to_set, char	*to_old);
void	dup_path(t_env *tmp_env, char *to_set, char *to_up);
char	*get_path(char *key, t_env *env);

#endif
