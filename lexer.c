#include "minishell.h"
/*
 !	ps = pointer to start
 ! es = end of str ~ no kneed for it for now
 ? q and eq will point to where token found
 */
int	getToken(char **ps,char *es, char **q, char **eq)
{
	char	*str;
	int		ret;

	str = *ps;
	while (str < es && ft_strchr(WHITESPACE, *str))
		str++;
	if (q)
		*q = str;
	ret = *str;
	if (*str == PIPE || *str == REDIRECT_IN
		|| *str == REDIRECT_OUT || *str == DELIMITER
		|| *str == REDIRECT_OUT_IN_APPEND_MD)
	{
		str++;
		if (*str == DELIMITER)
		{
			ret = '-';
			str++;
		}
		if (*str == REDIRECT_OUT_IN_APPEND_MD)
		{
			ret = '+';
			str++;
		}
	}
	else
	{
		ret = 'a';
		while (str < es && !ft_strchr(WHITESPACE, *str)
			&& !ft_strchr(SYMBOLS, *str))
			str++;
	}
	if (eq)
		*eq  = str;
	while (str < es && ft_strchr(WHITESPACE, *str))
		str++;
	*ps = str;
	return (ret);
}

int lexer(char **av)
{
	int	i;
	int j;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	i = 0;
	while (av[i][j])
	{
		getToken();
	}
}