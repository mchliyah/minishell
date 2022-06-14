#include "minishell.h"
/*
 	!1 @separate all by space like cmd|cmd to be cmd | cmd
 	!2 @ split all by space
 */


char	*get_args(char *s, int *j)
{
	int 	i;
	char	*r;
	char	c;

	i = *j;
	r = ft_strdup(" ");
	if (!r)
		return (NULL);
	while (s[i] && s[i] != PIPE && s[i] != REDIRECT_IN && s[i] != REDIRECT_OUT)
	{
		c = s[i];
		r = ft_strjoin(r, &c);
		if (!r)
			return (NULL);
	}
	return (r);
}

char	*get_cmd(char *str, int *i)
{
	char	**arr;
	char	*s;
	char	*args;
	char 	c;
	int		j;

	j = *i;
	arr = malloc(2 * sizeof(char *) + 1);
	s = ft_strdup(" ");
	args = ft_strdup(" ");
	if (!s || !args || !arr)
		return (NULL);
	while (str[j])
	{
		if (ft_isalpha(str[j]))
		{
			c = str[j];
			s = ft_strjoin(s, &c);
			if (!s)
				return (NULL);
		}
		// means maybe there is args of cmd
		else if (str[j] == SPACE)
		{
			j++;
			if (str[j] && str[j] != ) // exp ls -l || echo "hello"
				args = get_args(&str[j], &j);
		}
		else
			break ;
		j++;
	}
	arr[0] = s;
	arr[1] = args;
	arr[2] = 0;
	*i = j;
	return (s);
}
void	split_by_space(char *str, t_lexer *lexer)
{
	char 	c;
	int 	i;
	int		l;
	char	**sr;

	i = 0;
	l = 0;
	while (str[i])
	{
		get_cmd(str, &i);
		get_pipe(str, &i);
		get_rd
	}
}
int lexer(char *rln_str)
{
	int		token;
	size_t	len;
	size_t	i;
	int		i;
	int 	j;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	split_by_space(rln_str, lexer);

	return (EXIT_SUCCESS);
}