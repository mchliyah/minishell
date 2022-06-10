#include "minishell.h"

char	*get_next_token()

int lexer(char *rln_str)
{
	int		token;
	size_t	len;
	size_t	i;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	i = 0;
	len = ft_strlen(rln_str);
	printf("%s \n", rln_str);
	getToken(rln_str, lexer);
	return (EXIT_SUCCESS);
}