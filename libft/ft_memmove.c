/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:06:50 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/17 20:15:58 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstt;
	unsigned char	*srcc;
	size_t			i;

	i = 0;
	dstt = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	if (dstt == 0 && srcc == 0)
		return (NULL);
	if (dstt < srcc)
		ft_memcpy(dstt, srcc, len);
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			dstt[i] = srcc[i];
		}
	}
	return (dst);
}
