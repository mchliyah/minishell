/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:07:17 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/17 21:08:35 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		u;
	int		len;
	char	*str;

	u = 0;
	if (!s)
		return (0);
	len = ft_strlen(s);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[u])
	{
		str[u] = f(u, s[u]);
		u++;
	}
	str[len] = 0;
	return (str);
}
