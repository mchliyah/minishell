#include <stdio.h>
# include "includes/minishell.h"
int main()
{
	char *s = readline("d");
	printf("%s", s);
    return 0;
}

