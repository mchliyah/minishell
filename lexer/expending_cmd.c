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

void	ft_get_heredoc_helper(char **ptr, char **tmp)
{
	char	*save;
	int		i;

	i = 0;
	while (ptr[i])
	{
		save = ft_strjoin(*tmp, ptr[i]);
		free_strjoin(tmp, &ptr[i]);
		*tmp = save;
		i++;
	}
}

t_token	*ft_get_heredoc(t_token *token)
{
	char	c;
	char	*tmp;
	char	**ptr;

	if (is_double_quote_first(token->content))
	{
		c = '"';
		token->is_q = true;
	}
	else if (is_single_quote_first(token->content))
	{
		c = '\'';
		token->is_q = true;
	}
	else
		return (token);
	tmp = ft_strdup("");
	ptr = ft_split(token->content, c);
	if (!ptr)
		return (NULL);
	if (*ptr)
		ft_get_heredoc_helper(ptr, &tmp);
	free(ptr);
	free(token->content);
	token->content = tmp;
	return (token);
}

t_token	*scan_vars(t_token *token, t_env *env, int was_hered)
{
	if (was_hered == 2)
		token = ft_get_heredoc(token);
	else if (was_hered)
	{
		if (!is_single_quote_first(token->content)
			&& !is_double_quote_first(token->content)
			&& check_for_variables(token->content))
		{
			variable_expander(&token->content, env);
			if (*token->content == '\0')
			{
				token->type = SYNTAX_ERR;
			}
		}
	}
	else
		token->content = arg_iterator(token->content, env);
	return (token);
}
