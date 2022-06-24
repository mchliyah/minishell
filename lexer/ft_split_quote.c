/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:26:49 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/22 11:27:15 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static char	**c_str(char **str, char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	j = 0;
	while (s[i])
	{
		j = i;
		while (s[i] != c && s[i])
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				str[k] = ft_substr(s, j, (i - j) + 1);
				k++;
			}
			i++;
		}
		if (s[i] != 0)
			i++;
	}
	return (str);
}

static int	w_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] && (s[i + 1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**str;

	if (!s)
		return (0);
	count = w_count(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = c_str(str, s, c);
	str[count] = NULL;
	return (str);
}
