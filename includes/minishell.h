
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"



// typedef struct s_fdpip
// {
// 	int	*pips;
// 	int	*fdin;
// 	int	*fdout;
// 	int	i;
// 	int	j;
// }	t_fdinout;
void	print_tokens(t_pipe_line *pipeline);
int		generate_token(char *av, t_pipe_line *pipeline);
int		env_init(t_pipe_line *pipeline, char **env);
void	exec_cmd(t_pipe_line *c_line);
void	echo(t_list *cmd);

#endif