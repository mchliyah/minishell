#include "includes/minishell.h"

int main()
{
	int i = -1;
	char *s = strdup("'fdahfjash ");
	char **j = ft_split(s, ' ');
	while (j[++i])
		printf("%s\n", j[i]);

}