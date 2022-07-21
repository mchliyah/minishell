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
#include <stdbool.h>

static bool	is_double_quote_first(char const *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SINGLE_QUOTE)
			break ;
		else if (str[i] == L_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}

static bool	is_single_quote_first(char const *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == L_DOUBLE_QUOTE)
			break ;
		else if (str[i] == SINGLE_QUOTE)
			return (true);
	}
	return (false);
}

static char	**c_str(char **str, char const *s, char c)
{
	int		state;
	int		sq;
	int		q;
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	q = 0;
	sq = 0;
	printf("%s\n", s);
	while (s[i])
	{
		j = i;
		state = 0;
		if (is_double_quote_first(s))
			state = 1;
		while (s[i])
		{
			if (s[i] == L_DOUBLE_QUOTE && state == 1)
				q++;
			else if (s[i] == SINGLE_QUOTE && state == 0)
				sq++;
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')
				&& (((q == 0 || q % 2 == 0) && state == 1)
					|| ((sq == 0 || sq % 2 == 0) && state == 0)))
			{
				str[k] = ft_substr(s, j, i - j + 1);
				printf("---?? k %zu str %s|\n", k, str[k]);
				k++;
			}
			i++;
			if (s[i] == c && (((q == 0 || q % 2 == 0) && state == 1)
					|| ((sq == 0 || sq % 2 == 0) && state == 0)))
				break ;
		}
		if (s[i] != 0)
		{
			i++;
			if (s[i] == '\0' && (((q == 0 || q % 2 != 0) && state == 1)
					|| ((sq == 0 || sq % 2 != 0) && state == 0)) && s[i - 1] != SPACE)
			{
				str[k] = ft_substr(s, j, (i - j));
				printf("--->> k %zu str %s\n", k, str[k]);
				k++;
			}
		}
	}
	return (str);
}

static int	w_count(char const *s, char c)
{
	int	state;
	int	j;
	int	i;
	int	count;
	int	sq;

	count = 0;
	i = 0;
	j = 0;
	sq = 0;
	state = -1;
	if (is_double_quote_first(s))
		state = 1;
	else if (is_single_quote_first(s))
		state = 0;
	while (s[i])
	{
		if (s[i] == L_DOUBLE_QUOTE && state == 1)
			j++;
		else if (s[i] == SINGLE_QUOTE && state == 0)
			sq++;
		if (
			(s[i] != c || s[i]) && (s[i + 1] == c || s[i + 1] == '\0')
		)
		{
			if (
				((j == 0 || j % 2 == 0) && state == 1) || s[i + 1] == '\0'
			)
			{
				count++;
				if (is_single_quote_first(s))
					state = 0;
				else if (is_double_quote_first(s))
					state = 1;
				else
					state = -1;
			}
			else if (((sq == 0 || sq % 2 == 0) && state == 0) || s[i + 1] == '\0')
			{
				count++;
				if (is_single_quote_first(s))
					state = 0;
				else if (is_double_quote_first(s))
					state = 1;
				else
					state = -1;
			}
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
	printf("cou %d\n", count);
	str[count] = NULL;
	return (str);
}
