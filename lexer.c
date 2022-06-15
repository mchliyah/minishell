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

char	**get_cmd(char *str, int *i)
{
	char	**arr;
	char	*s;
	char	*args;
	char 	c;
	int		j;

	j = *i;
	arr = malloc(2 * sizeof(char *) + 1);
	s = ft_strdup("");
	args = ft_strdup("");
	if (!s || !args || !arr)
		return (NULL);
	while (str[j])
	{
		if (ft_isalpha(str[j]))
		{
			c = str[j];
			s = ft_strjoin(s, &c);
			printf("s while joining %s\n", s);
			if (!s)
				return (NULL);
		}
		// means maybe there is args of cmd
//		else if (str[j] == SPACE)
//		{
//			j++;
//			// exp ls -l || echo "hello"
//			if (str[j] && str[j] != PIPE && str[j] != REDIRECT_IN && str[j] != REDIRECT_OUT)
//				args = get_args(&str[j], &j);
//		}
		else
			break ;
		j++;
	}
	printf("s %s\n", s);
	arr[0] = s;
	arr[1] = args;
	arr[2] = 0;
	*i = j;
	return (arr);
}
void	split_by_space(char *str, t_lexer *lexer)
{
	char 	c;
	int 	i;
	int		l;
	char	**sr;

	i = 0;
	l = 0;
	sr = get_cmd(str, &i);
	while (sr[l])
	{
		printf("%s\n", sr[l]);
		l++;
	}
}
int lexer(char *rln_str)
{
	int		token;
	size_t	len;
	size_t	i;
	int 	j;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	split_by_space(rln_str, lexer);

	return (EXIT_SUCCESS);
}