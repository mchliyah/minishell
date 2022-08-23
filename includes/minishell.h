/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:07:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/22 23:41:05 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

//# define PVL(x, y) fprintf(stderr, "%s:%d %s = " y, __FILE__, __LINE__, #x, x)
//# define PV(x, y) fprintf(stderr, "%s = " y, #x, x)
# define HERE fprintf(stderr, "** In %s:%d **\n", __FILE__, __LINE__)

//void	print_tokens(t_p_line *pipeline);
void	rl_replace_line(char *txt, int i);
int		init_pipes(t_data **data);
t_data	*init_data(int ac, char **av, t_data *data, char **envp);
void	shelvl(t_env **env);
int		iterator(t_p_line *this_pipe, t_data **exec);
void	sort_exp(t_env **exp);
t_env	*get_env(char **envp);
char	**get_env_char(t_env *env);
void	handle_sigint(int sig);
//void	exec_cmd(t_list *cmd, char **envp, t_data *exec);

//free
void	free_pipe(t_p_line *pipeline);
void	free_list(t_list *to_f);
void	free_data(t_data *data);
void	parser_main(char *str_rln, t_data **data);
void	main_parent_waiting(int count, t_data **data);
void	get_tkn_exec(char *str_rln, t_data **data, t_p_line **pipeline);

#endif
