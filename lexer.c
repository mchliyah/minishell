#include "minishell.h"
/*
 	!1 @separate all by space like cmd|cmd to be cmd | cmd
 	!2 @ split all by space
 */
int	getToken(char **ps, char *es, char **q, char **eq)
{
	(void)ps;
	(void)es;
	(void)q;
	(void)eq;
	return (0);
}

char	*get_args(char *s, int *j)
{
	int		i;
	char	*r;
	char	c;

	i = *j;
	r = ft_strdup(" ");
	if (!r)
		return (NULL);
	while (s[i] && ft_isalpha(s[i]))
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
	char	*s;
	char	*args;
	char	c;
	int		j;

	j = *i;
	s = ft_strdup(" ");
	args = ft_strdup(" ");
	if (!s || !args)
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
		else if (str[j] == SPACE)
		{
			j++;
			if (str[j] && str[j] == MINUS)
			{
				args = get_args(&str[j], &j);
			}
		}
		else
			break ;
		j++;
	}
	*i = j;
	return (s);
}
void	split_by_space(char *str, t_lexer *lexer)
{
	char	c;
	int		i;
	int		l;
	char	**sr;

	i = 0;
	l = 0;
	(void)c;
	(void)sr;
	(void)lexer;
	while (str[i])
	{
		get_cmd(str, &i);
		// get_pipe(str, &i);
		// get_rd();
	}
}
int lexer(char *rln_str)
{
	int		token;
	size_t	len;
	size_t	i;
	t_lexer	*lexer;

	i = 0;
	len = 0;
	token = 0;
	lexer = malloc(sizeof(t_lexer));
	split_by_space(rln_str, lexer);
	return (EXIT_SUCCESS);
}