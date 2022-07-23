/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:46:35 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/22 09:46:38 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_inside_squote(char const *s, char **str, int i, size_t *k, char c, int j)
{
	(void)c;
	while (s[i] != SINGLE_QUOTE && s[i])
	{
		i++;
	}
	if (s[i] == SINGLE_QUOTE || s[i] == '\0')
	{
		str[*k] = ft_substr(s, j, i - j + 1);
		(*k)++;
		i++;
	}
	return (i);
}

int	get_inside_quote(char const *s, char **str, int i, size_t *k, char c, int j)
{
	(void)c;
	while (s[i] != R_DOUBLE_QUOTE && s[i])
	{
		i++;
	}
	if (s[i] == R_DOUBLE_QUOTE || s[i] == '0')
	{
		str[*k] = ft_substr(s, j, i - j + 1);
		(*k)++;
		i++;
	}
	return (i);
}

int	get_words(char const *s, char **str, int i, size_t *k, char c, int j)
{
	while (s[i] != R_DOUBLE_QUOTE && s[i] != SINGLE_QUOTE && s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			str[*k] = ft_substr(s, j, i - j + 1);
			(*k)++;
		}
		i++;
	}
	return (i);
}