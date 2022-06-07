/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:02:06 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 11:57:21 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		a;
	char	*sub;

	a = 0;
	if (!s)
		return (0);
	if ((len + 1) > ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	if (len < 0)
		return (0);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	if (s == 0)
		return (NULL);
	while (len > 0 && start < ft_strlen(s))
	{
		sub[a] = s[start];
		start++;
		a++;
		len--;
	}
	sub[a] = '\0';
	return (sub);
}
