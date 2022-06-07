/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:26:04 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 17:54:03 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	smallf(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	return (i);
}

static int	ft_fill(const char *str, int i, int neg)
{
	long	tmp;
	long	num;

	tmp = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		if (num < tmp && neg == -1)
			return (0);
		if (num < tmp)
			return (-1);
		tmp = num;
		i++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			nega;
	long long	num;

	nega = 1;
	i = smallf(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nega *= -1;
		i++;
	}
	num = ft_fill(str, i, nega);
	num = nega * num;
	return (num);
}
