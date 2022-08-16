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

bool	check_for_variables(const char *str)
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

int	expend_var(char **ptr, int i, char *arg, t_env *env)
{
	char	*tmp;
	int		s;

	i++;
	s = i;
	if (ft_isdigit(arg[i]))
		i++;
	else if (arg[i] == '?')
	{
		*ptr = ft_strjoin(*ptr, ft_itoa(g_status));
		i++;
	}
	else
	{
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
			i++;
	}
	tmp = ft_substr(arg, s, i - s);
	if (!tmp)
		exit(1);
	tmp = get_form_my_env(tmp, env);
	if (!tmp)
		tmp = ft_strdup("");
	*ptr = ft_strjoin(*ptr, tmp);
	return (i);
}

char	*variable_expander(char *s, t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '?'
				|| ft_isalnum(s[i + 1])))
			i = expend_var(&str, i, s, env);
		str = join_string(str, s[i]);
		i++;
	}
	return (str);
}

char	*single_quote_remove(char *s, int *i)
{
	int		st;
	char	*ret;

	(*i)++;
	st = *i;
	while (s[*i] && s[*i] != SINGLE_QUOTE)
	{
		(*i)++;
	}
	ret = ft_substr(s, st, *i - st);
	return (ret);
}

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
		ret = variable_expander(ret, env);
	return (ret);
}

void	get_status(int *i, char *s, t_env *env, char **str)
{
	char	*tmp;
	int		st;
	char	*var;

	st = *i;
	if (s[(*i)++] == '?')
		var = ft_itoa(g_status);
	else
	{
		if (ft_isdigit(s[*i]))
			(*i)++;
		else
		{
			while ((ft_isalnum(s[*i]) || s[*i] == '_') && s[*i])
				(*i)++;
		}
		tmp = ft_substr(s, st, *i - st);
		var = get_form_my_env(tmp, env);
		if (!var)
			var = ft_strdup("");
	}
	*str = ft_strjoin(*str, var);
}

char	*string_getter(char *s, int *i, t_env *env)
{
	char	*str;

	str = ft_strdup("");
	while (s[*i])
	{
		if (s[*i] == '$' && (s[*i + 1] == '?'
				|| ft_isalnum(s[*i + 1])))
		{
			(*i)++;
			get_status(i, s, env, &str);
		}
		else if (s[*i] == '$' && (s[*i + 1] == SINGLE_QUOTE
				|| s[*i + 1] == L_DOUBLE_QUOTE))
			(*i)++;
		else
		{
			str = join_string(str, s[*i]);
			(*i)++;
		}
		if (s[*i] == SINGLE_QUOTE || s[*i] == L_DOUBLE_QUOTE)
			break ;
	}
	return (str);
}

char	*arg_iterator(char *content, t_env *env)
{
	char	*saver;
	char	*c;
	int		i;

	i = 0;
	saver = ft_strdup("");
	while (content[i])
	{
		if (content[i] == SINGLE_QUOTE)
			c = single_quote_remove(content, &i);
		else if (content[i] == L_DOUBLE_QUOTE)
			c = double_quote_remove(content, &i, env);
		else
		{
			c = string_getter(content, &i, env);
			i--;
		}
		saver = ft_strjoin(saver, c);
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
