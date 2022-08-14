/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:18:09 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/02 16:32:19 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*p;
	char	*start;

	p = malloc (sizeof (char) * ft_strlen(src) + 1);
	if (!p)
		return (0);
	start = p;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (start);
}
