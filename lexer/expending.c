/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:41:01 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/15 12:41:03 by ael-mous         ###   ########.fr       */
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

char	*rm_quote(char *arg, t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	if (
		(arg[i] == R_DOUBLE_QUOTE && arg[i + 1] == '$'
			&& (ft_isalnum(arg[i + 2]) || arg[i + 2] == '?'))
	)
		str = ft_strjoin(str, get_variable(arg, env));
	else
		str = ft_strjoin(str, get_simple_word(arg, env));
	free(arg);
	arg = NULL;
	return (str);
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
		return (NULL);
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

t_token	*remove_quoted_args(t_token *token, t_env *env)
{
	int	a;

	a = 0;
	while (token->arg->next)
	{
		if (is_there_quote(token->arg->content))
			token->arg->content = rm_quote(token->arg->content, env);
		else if (is_there_squote(token->arg->content))
			token->arg->content = rm_squote(token->arg->content);
		else if (check_for_variables(token->arg->content))
			token->arg->content = get_variable(token->arg->content, env);
		printf("*** %s\n", token->arg->content);
		token->arg = token->arg->next;
	}
	return (token);
}
