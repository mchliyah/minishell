/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:00:05 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 10:44:23 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 	* function locates the first occurrence of 'c' in
    * the string pointed to by s.  The terminating null character is considered to be
	* part of the string; therefore if c is `\0', the functions locate the terminating
	* `\0'.
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char)c;
	while (s[i] != 0)
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}
