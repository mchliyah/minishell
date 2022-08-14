/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:07:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/14 01:05:43 by mchliyah         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TMP_FILE "/Users/$USER/.TemporaryItems/.tmp_here_doc"

# define PVL(x, y) fprintf(stderr, "%s:%d %s = " y, __FILE__, __LINE__, #x, x)
# define PV(x, y) fprintf(stderr, "%s = " y, #x, x)
# define HERE fprintf(stderr, "** In %s:%d **\n", __FILE__, __LINE__)


//void	print_tokens(t_p_line *pipeline);

t_data	*init_data(int ac, char **av, t_data *data, char **envp);

int		iterator(t_p_line *this_pipe, t_data **exec);
void    sort_exp(t_env **exp);
t_env	*get_env(char **envp);
//void	exec_cmd(t_list *cmd, char **envp, t_data *exec);

//free
void	free_pipe(t_p_line *pipeline);
void	free_list(t_list *to_f);
void	free_data(t_data *data);


#endif