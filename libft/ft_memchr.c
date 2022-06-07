/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:52:48 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 11:29:48 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	cc;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (s1[i] == cc)
			return ((unsigned char *)s1 + i);
		i++;
	}
	return (0);
}
