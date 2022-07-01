
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

// typedef struct s_fdpip
// {
// 	int	*pips;
// 	int	*fdin;
// 	int	*fdout;
// 	int	i;
// 	int	j;
// }	t_fdinout;

t_fdinout	*init_fds(t_list	*lst_tok, t_fdinout	*fds);
void		print_tokens(t_pipe_line *pipeline);

#endif