
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <stdbool.h>

int g_status;


// typedef struct s_fdpip
// {
// 	int	*pips;
// 	int	*fdin;
// 	int	*fdout;
// 	int	i;
// 	int	j;
// }	t_fdinout;
void	print_tokens(t_pipe_line *pipeline);
int		generate_token(char *av, t_pipe_line *pipeline, char **env);
int		env_init(t_pipe_line *pipeline, char **env);
void	exec_cmd(t_pipe_line *c_line, char **env);
char	*get_path(char *path, t_env *env);
void	echo(t_list *cmd);
void	env_cmd(t_pipe_line *p_line);
void	cd_cmd(t_list	*c_line, t_env *env);
void	pwd_cmd(t_pipe_line *p_line);

#endif