/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:48:56 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/05 16:41:33 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	cc;

	i = 0;
	len = 0;
	cc = (char)c;
	while (s[len] != 0)
		len++;
	while (len >= 0)
	{
		if (s[len] == cc)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
