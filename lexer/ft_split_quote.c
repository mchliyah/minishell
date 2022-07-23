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

//static bool	is_double_quote_first(char const *str)
//{
//	int	i;
//
//	i = -1;
//	while (str[++i])
//	{
//		if (str[i] == SINGLE_QUOTE)
//			break ;
//		else if (str[i] == L_DOUBLE_QUOTE)
//			return (true);
//	}
//	return (false);
//}
//
//static bool	is_single_quote_first(char const *str)
//{
//	int	i;
//
//	i = -1;
//	while (str[++i])
//	{
//		if (str[i] == L_DOUBLE_QUOTE)
//			break ;
//		else if (str[i] == SINGLE_QUOTE)
//			return (true);
//	}
//	return (false);
//}
//

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
			if (s[i] == L_DOUBLE_QUOTE)
			{
				i++;
				i = get_inside_quote(s, str, i, &k, c, j);
			}
			else if (s[i] == SINGLE_QUOTE) {
				i++;
				i = get_inside_squote(s, str, i, &k, c, j);
			}
			else {
				i = get_words(s, str, i, &k, c, j);
			}
		}
		if (s[i] != 0)
			i++;
	}
	return (str);
}
/*
static int	w_count(char const *s, char c)
{
	int	state;
	int	j;
	int	i;
	int	count;
	int	t;
	int sq;

	count = 0;
	i = 0;
	j = 0;
	sq = 0;
	state = -1;
	t = 0;
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
			(s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			|| (s[i] == c && s[i + 1] == '\0')
		)
		{
			if (
				((j == 0 || j % 2 == 0) && state == 1) || s[i + 1] == '\0'
			)
			{
				count++;
				if (s[i] == L_DOUBLE_QUOTE)
					t = 1;
				if (is_single_quote_first(&s[i + t]))
					state = 0;
				else if (is_double_quote_first(&s[i + t]))
					state = 1;
				else
					state = -1;
			}
			else if (((sq == 0 || sq % 2 == 0) && state == 0) || s[i + 1] == '\0')
			{
				count++;
				if (s[i] == SINGLE_QUOTE)
					t = 1;
				if (is_single_quote_first(&s[i + t]))
					state = 0;
				else if (is_double_quote_first(&s[i + t]))
					state = 1;
				else
					state = -1;
			}
		}
		i++;
	}
	return (count);
}*/

static int	w_count(char const *str, char c)
{
	int	word;
	int	j;

	word = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j++;
		if (str[j] == SINGLE_QUOTE)
		{
			j++;
			while (str[j])
			{
				j++;
				if ((str[j] == SINGLE_QUOTE && (str[j + 1] == c
							|| str[j + 1] == '\0')) || str[j] == '\0')
				{
					word++;
					if (str[j])
						j++;
					break ;
				}
			}
		}
		else if (str[j] == L_DOUBLE_QUOTE)
		{
			j++;
			while (str[j])
			{
				j++;
				if ((str[j] == R_DOUBLE_QUOTE && (str[j + 1] == c
							|| str[j + 1] == '\0')) || str[j] == '\0')
				{
					word++;
					if (str[j])
						j++;
					break ;
				}
			}
		}
		else
		{
			while (str[j] && str[j] != c)
				j++;
			while (str[j] && str[j] == c)
				j++;
			word++;
		}
	}
	if (str[0] == c)
		word--;
	return (word);
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
	printf("cou %d\n", count);
	str = c_str(str, s, c);
	str[count] = NULL;
	int i = 0;
	while (str[i])
	{
		printf("--->%s<--\n", str[i]);
		i++;
	}
	return (str);
}
