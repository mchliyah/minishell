/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:16:05 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 17:57:23 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destt;
	unsigned char	*srcc;

	destt = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	i = 0;
	if (destt == 0 && srcc == 0)
		return (NULL);
	if (dst != src)
	{
		while (i < n)
		{
			destt[i] = srcc[i];
			i++;
		}
	}
	return (dst);
}
