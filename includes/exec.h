/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:57:21 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/21 19:00:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structs.h"
# include "minishell.h"
# include "../libft/libft.h"

//exec
void	to_std(t_list *cmd, t_data **data);
bool	exec_cmd(t_list *cmd, t_data **exec);
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
void	ret_err_exp(t_pair *to_exp, char *args);
void	env_cmd(t_env *env);
void	export_cmd(t_env **exp, t_env **env, t_list *c_line);
void	unset_cmd(t_env **env, t_list *cmd);
int		check_exp(char *str);
int		elem_exist(t_env *env, char *arg);
char	*env_dup(char *tmp_val, int i, int j);
void	add_elem(t_env **env, t_pair *to_exp, int exist);
void	exp_error(int ret, char *str);
//cd cmand
void	cd_cmd(t_list	*c_line, t_env *env);
char	*get_path(char *path, t_env *env);
void	dup_path(t_env *tmp_env, char *to_set, char *to_up);
char	*get_path(char *key, t_env *env);
//other builtins
int		is_builtins(char *content);
void	buuiltins(char *content, t_list *cmd, t_data **data);
t_env	*update_path(t_env *env, char *to_set, char	*to_old);
void	echo(t_list *cmd);
void	pwd_cmd(t_env *env);
int		exit_cmd(t_list *cmd);
// here doc
int		count_here(t_list *list);
void	close_here_doc_fd(t_data **data, int count);
int		wait_heredoc(t_data **data, int pid, int count);
int		get_here_doc(t_list *cmd, t_data **data);
int		check_for_heredoc(t_p_line *pipe, t_data **data);
void	shelvl(t_env **env);
void	ft_close_fd(t_data **data);
int		append_file(t_data **data, t_list *cmd, char *file);
void	fd_error_exit(char *str);
void	redirect_ins(char *file, t_list *iterator, t_data **data);

#endif
