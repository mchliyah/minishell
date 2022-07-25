/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:41:01 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/24 22:59:29 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_there_squote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == L_DOUBLE_QUOTE)
			break ;
		if (arg[i] == SINGLE_QUOTE)
			return (true);
	}
	return (false);
}

int	is_there_quote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == SINGLE_QUOTE)
			break ;
		if (arg[i] == L_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}

bool	check_for_variables(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (true);
	}
	return (false);
}

char	*rm_quote(char *arg, t_env *env, int state)
{
	int		i;

	i = 0;
	if (arg[i] == R_DOUBLE_QUOTE && arg[i + 1] == '$'
		&& (ft_isalnum(arg[i + 2]) || arg[i + 2] == '?'))
		return (get_variable(arg, env, state));
	else
		return (get_simple_word(arg, env, state));
}

char	*rm_squote(char *arg)
{
	char	*ptr;
	char	**str;
	int		i;

	i = 0;
	if (arg[i] == '$' && arg[i + 1] == SINGLE_QUOTE)
		i++;
	str = ft_split(arg, '\'');
	free(arg);
	arg = NULL;
	if (!str)
	{
		return (NULL);
	}
	ptr = ft_strdup("");
	if (!ptr)
		printf("a Null returned in rm squote\n");
	while (str[i])
	{
		ptr = ft_strjoin(ptr, str[i]);
		if (!ptr)
			printf("a Null returned in rm squote");
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (ptr);
}

t_arg	*remove_quoted_args(t_arg *token, t_env *env)
{
	t_arg	*arg;

	arg = token;
	while (token)
	{
		if (is_there_quote(token->content))
			token->content = rm_quote(token->content, env, 1);
		else if (is_there_squote(token->content))
			token->content = rm_squote(token->content);
		else if (check_for_variables(token->content))
			token->content = get_variable(token->content, env, 1);
		token = token->next;
	}
	return (arg);
}
