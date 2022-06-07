
#include "minishell.h"

int main(int ac, char **av)
{
	(void)ac;
	lexer(av);
	return (0);
}