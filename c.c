#include <stdio.h>

int main(int ac , char **av)
{
    printf(" ac === %d\n", ac);
    for (int i = 0; av[i]; i++)
        printf ("|%s|\n", av[i]);
}