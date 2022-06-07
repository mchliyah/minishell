/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:19:17 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 11:32:51 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		l;
	char	*sub;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && (ft_strchr(set, s1[i]) != NULL))
		i++;
	j = ft_strlen(s1) - 1;
	if (j == -1)
		j = 0;
	while (j && (ft_strchr(set, s1[j]) != NULL))
		j--;
	l = j - i + 1;
	if (l <= 0)
	{
		sub = (char *)malloc(1);
		sub[0] = 0;
	}
	else
		sub = ft_substr(s1, i, (j - i) + 1);
	return (sub);
}
