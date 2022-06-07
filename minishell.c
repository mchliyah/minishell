
#include "minishell.h"

int main(char **av)
{
	lexer(av);
	printf("%c", TS_L_PARENS);
	return (0);
}