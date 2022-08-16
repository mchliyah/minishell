/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:48:21 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/10 19:58:09 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_token	*scan_vars(t_token *token, t_env *env, int was_hered)
{
	char	c;
	char	*tmp;
	char	**ptr;

	if (was_hered == 2)
	{
		if (is_double_quote_first(token->content))
			c = '"';
		else if (is_single_quote_first(token->content))
			c = '\'';
		else
			return (token);
		ptr = ft_split(token->content, c);
		if (!ptr)
			return (NULL);
		if (!*ptr)
			tmp = ft_strdup("");
		else
		{
			tmp = (*ptr)++;
			while (*ptr)
			{
				tmp = ft_strjoin(tmp, *ptr);
				free(*ptr);
				(*ptr)++;
			}
		}
		free(ptr);
		free(token->content);
		token->content = tmp;
	}
	else
		token->content = arg_iterator(token->content, env);
	return (token);
}
