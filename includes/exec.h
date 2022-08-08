/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:57:21 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/08 00:58:59 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structs.h"
# include "minishell.h"
# include "../libft/libft.h"
//exec
void	to_std(t_env *env, char **envp, t_list *cmd, t_data **data);
void	exec_cmd(t_list *cmd, char **envp, t_data **exec);
// void	to_std(t_env *env, char **envp, t_list *cmd);
//char	*get_path(char *path, t_env *env);

void	env_cmd(t_env *env);
void	cd_cmd(t_list	*c_line, t_env *env);
//void	pwd_cmd(t_env **env, t_data *exec);
void	unset_cmd(t_env **env, t_list *cmd);
char	**arr_arg(t_list *cmd);
t_env	*start(char **envp);
t_pair	*init_pair(char *tmp_val);
char	**arr_arg(t_list *cmd);
//env&exp
void	env_cmd(t_env *env);
void	export_cmd(t_data **data, t_list *c_line);
void	unset_cmd(t_env **env, t_list *cmd);
int		check_exp(char *str);
int		elem_exist(t_env *env, char *arg);
char	*env_dup(char *tmp_val, int i, int j);
void	dup_exist_elem(t_env **tmp_in, t_pair *to_exp);
t_env	*dup_not_exist_elem(t_pair *to_exp);
void	exp_error(int ret, char *str);
//cd cmand
void	cd_cmd(t_list	*c_line, t_env *env);
char	*get_path(char *path, t_env *env);
void	dup_path(t_env *tmp_env, char *to_set, char *to_up);
char	*get_path(char *key, t_env *env);
//other builtins
t_env	*update_path(t_env *env, char *to_set, char	*to_old);
void	echo(t_list *cmd);
void	pwd_cmd(t_env *env);
int		exit_cmd(t_list *cmd);
// here doc
int		here_doc(char *key_stop, t_data **data);

#endif
