
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

typedef struct s_fdpip
{
	int	*pips;
	int	*fdin;
	int	*fdout;
}	t_fdinout;

#endif