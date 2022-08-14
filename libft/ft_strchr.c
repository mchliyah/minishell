/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:49:58 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 23:31:05 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}
