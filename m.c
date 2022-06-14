#include <stdio.h>
int	 gcd(int a, int c)
{
	if (c == 0)
		return a;
	else
		return gcd(c, a % c);
}

int main()
{
	printf("%d", gcd(16, 10));
    return 0;
}

