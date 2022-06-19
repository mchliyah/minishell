
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

typedef struct s_fdpip
{
	int	*pips;
	int	*fdin;
	int	*fdout;
	int	i;
	int	j;
}	t_fdinout;

#endif