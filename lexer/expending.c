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

extern int	g_status;

char	*double_quote_remove(char *s, int *i, t_env *env)
{
	int		st;
	char	*ret;

	(*i)++;
	st = *i;
	while (s[*i] && s[*i] != L_DOUBLE_QUOTE)
		(*i)++;
	ret = ft_substr(s, st, *i - st);
	if (check_for_variables(ret))
		variable_expander(&ret, env);
	return (ret);
}

void	get_status(int *i, char *s, t_env *env, char **str)
{
	char	*tmp;
	int		st;
	char	*var;

	st = *i;
	if (s[(*i)] == '?')
	{
		var = ft_itoa(g_status);
		(*i)++;
	}
	else
	{
		get_last(s, i);
		tmp = ft_substr(s, st, *i - st);
		var = get_form_my_env(tmp, env);
		if (!var)
			var = ft_strdup("");
		free(tmp);
	}
	tmp = ft_strjoin(*str, var);
	free_strjoin(str, &var);
	*str = tmp;
}

char	*string_getter(char *s, int *i, t_env *env)
{
	char	*str;

	str = ft_strdup("");
	while (s[*i])
	{
		if (s[*i] == '$' && (s[*i + 1] == '?'
				|| ft_isalnum(s[*i + 1]) || s[*i + 1] == '_'))
		{
			(*i)++;
			get_status(i, s, env, &str);
		}
		else if (s[*i] == '$' && (s[*i + 1] == SINGLE_QUOTE
				|| s[*i + 1] == L_DOUBLE_QUOTE))
			(*i)++;
		else
		{
			join_string(&str, s[*i]);
			(*i)++;
		}
		if (s[*i] == SINGLE_QUOTE || s[*i] == L_DOUBLE_QUOTE)
			break ;
	}
	return (str);
}

char	*arg_iterator(char *content, t_env *env)
{
	char	*tmp;
	char	*saver;
	char	*str;
	int		i;

	i = 0;
	saver = ft_strdup("");
	while (content[i])
	{
		if (content[i] == SINGLE_QUOTE)
			str = single_quote_remove(content, &i);
		else if (content[i] == L_DOUBLE_QUOTE)
			str = double_quote_remove(content, &i, env);
		else
		{
			str = string_getter(content, &i, env);
			i--;
		}
		tmp = ft_strjoin(saver, str);
		free_strjoin(&saver, &str);
		saver = tmp;
		i++;
	}
	free(content);
	return (saver);
}

t_arg	*remove_quoted_args(t_arg *token, t_env *env)
{
	t_arg	*arg;

	arg = token;
	while (token)
	{
		token->content = arg_iterator(token->content, env);
		token = token->next;
	}
	return (arg);
}
