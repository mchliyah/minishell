/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:26:49 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/27 22:22:57 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static char	**c_str(char **str, char const *s, char c)
{
	int		q;
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	q = 0;
	while (s[i])
	{
		j = i;
		while (s[i])
		{
			if (s[i] == L_DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
				q++;
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')
				&& (q == 0 || q % 2 == 0))
			{
				str[k] = ft_substr(s, j, i - j + 1);
				k++;
			}
			i++;
			if (s[i] == c && (q == 0 || q % 2 == 0))
				break ;
		}
		if (s[i] != 0)
			i++;
		if (s[i] == '\0' && (q == 0 || q % 2 != 0))
		{
			str[k] = ft_substr(s, j, (i - j));
			k++;
		}
	}
	return (str);
}

static int	w_count(char const *s, char c)
{
	int	j;
	int	i;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == L_DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
			j++;
		if ((s[i] != c || s[i]) && (s[i + 1] == c || s[i + 1] == '\0')
			&& (j == 0 || j % 2 == 0 || s[i + 1] == '\0'))
		{
				count++;
		}
		i++;
	}
	return (count);
}

char	**ft_split_arg(char const *s, char c)
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
