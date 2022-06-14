/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:43:46 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/20 11:15:33 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 *  iterate over a string
 *  sends address of the current index
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	u;

	u = 0;
	if (s != NULL)
	{
		while (s[u])
		{
			f(u, &s[u]);
			u++;
		}
	}
}
