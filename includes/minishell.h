/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:07:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/04 13:34:26 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <sys/types.h>
 #include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

int g_status;

# define PV(x, y) fprintf(stderr, "%s = " y, #x, x)
# define PVL(x, y) fprintf(stderr, "%s:%d %s = " y, __FILE__, __LINE__ #x, x)
# define HERE fprintf(stderr, "** In %s:%d **\n", __FILE__, __LINE__)

void	print_tokens(t_pipe_line *pipeline);
int	generate_token(char *rln_str, t_pipe_line **pipeline, t_env *env,
	t_data **data);
int		iterator(t_pipe_line *this_pipe, char **envp, t_data **exec);
void    sort_exp(t_env **exp);
t_env	*get_env(char **envp);


#endif