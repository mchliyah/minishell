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

//leaks
int	expend_var(char **ptr, int i, char *arg, t_env *env)
{
	char	*save;
	char	*tmp;
	int		s;

	i++;
	s = i;
	if (ft_isdigit(arg[i]))
		i++;
	else if (arg[i] == '?')
	{
		save = ft_itoa(g_status);
		tmp = ft_strjoin(*ptr, save);
		free_strjoin(ptr, &save);
		*ptr = tmp;
		i++;
	}
	else
	{
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
			i++;
	}
	tmp = ft_substr(arg, s, i - s);
//	printf("%s\n", tmp);
	if (!tmp)
		exit(1);
	tmp = get_form_my_env(tmp, env);
	if (!tmp)
		tmp = ft_strdup("");
	save = ft_strjoin(*ptr, tmp);
	free(*ptr);
	*ptr = save;
	return (i);
}

void	variable_expander(char **s, t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (s[0][i])
	{
		if (s[0][i] == '$' && (s[0][i + 1] == '?'
				|| ft_isalnum(s[0][i + 1])))
			i = expend_var(&str, i, *s, env);
		join_string(&str, s[0][i]);
		i++;
	}
	free(*s);
	*s = str;
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
		variable_expander(&ret, env);
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
	tmp = ft_strjoin(*str, var);
	//free_strjoin(str, &var);
	free(*str);
	*str = tmp;
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
	printf("%s\n", saver);
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
