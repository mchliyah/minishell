
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <sys/types.h>
 #include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include <stdbool.h>

# define PV(x, y) fprintf(stderr, "%s = " y, #x, x)
# define PVL(x, y) fprintf(stderr, "%s:%d %s = " y, __FILE__, __LINE__ #x, x)
# define HERE fprintf(stderr, "%s:%d here\n", __FILE__, __LINE__)

// int g_status;

typedef struct s_data
{
    t_env   *env;
    t_env   *exp;
    int		exit;
    int     pip_nb;
	int	    *pips;
	int	    *fdin;
	int	    *fdout;
}	t_data;

void	print_tokens(t_pipe_line *pipeline);
int	generate_token(char *rln_str, t_pipe_line **pipeline, t_env *env,
	t_data **data);
void    sort_exp(t_env **exp);
t_env	*get_env(char **envp);


#endif