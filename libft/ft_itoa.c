/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:38:21 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 17:56:29 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ncount(long i)
{
	int			counter;

	counter = 1;
	if (i < 0)
	{
		i = -i;
		counter++;
	}
	while (i > 0)
	{
		i = i / 10;
		counter++;
	}
	if (counter == 1)
		counter = 2;
	return (counter);
}

static char	*ntcnv(long c)
{
	int			count;
	long		lo;
	char		*nu;
	int			j;

	count = (ncount((long)c) - 1);
	j = count;
	nu = (char *)malloc(count + 1);
	if (!nu)
		return (0);
	if (c == 0)
		nu[0] = c + 48;
	else if (c < 0)
	{
		c = -c;
		nu[0] = '-';
	}	
	while (c > 0)
	{
		lo = c % 10;
		c = c / 10;
		nu[--count] = lo + 48;
	}
	nu[j] = '\0';
	return (nu);
}

char	*ft_itoa(int c)
{
	char	*num;

	num = ntcnv(c);
	return (num);
}
