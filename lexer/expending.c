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

char	*rm_quote(char *arg, t_pipe_line *env)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == L_DOUBLE_QUOTE && (arg[i + 1] == '$'
				|| ft_isalnum(arg[i + 1])))
		{
			i++;
			if (arg[i + 1] == R_DOUBLE_QUOTE)
			{
				printf(">><<\n");
				return (get_simple_word(arg));
			}
		}
		else
			return (get_variable(arg, env));
		i++;
	}
	return (NULL);
}

char	*rm_squote(char *arg)
{
	char	*ptr;
	char	**str;
	int		i;

	i = 0;
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

t_token	*remove_quoted_args(t_token *token, t_pipe_line *env)
{
	int	a;

	a = 0;
	(void )env;
	while (token->args[a])
	{
		printf("token  %s\n", token->args[a]);
		if (is_there_quote(token->args[a])) {
			token->args[a] = rm_quote(token->args[a], env);
			printf("token>>  %s|\n", token->args[a]);
		}
		else if (is_there_squote(token->args[a])) {
			token->args[a] = rm_squote(token->args[a]);
		}
		else if (check_for_variables(token->args[a])) {
			token->args[a] = get_variable(token->args[a], env);
		}
		a++;
	}
	return (token);
}
