/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_file_holeder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:01:00 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/20 23:01:02 by ael-mous         ###   ########.fr       */
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

void	expend_status(char **ptr)
{
	char	*save;
	char	*tmp;

	save = ft_itoa(g_status);
	tmp = ft_strjoin(*ptr, save);
	free_strjoin(ptr, &save);
	*ptr = tmp;
}

int	expend_var(char **ptr, int i, char *arg, t_env *env)
{
	char	*save;
	char	*tmp;
	char	*str;
	int		s;

	i++;
	s = i;
	if (ft_isdigit(arg[i]) || arg[i] == '?')
	{
		if (arg[i] == '?')
			expend_status(ptr);
		i++;
	}
	else
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
			i++;
	str = ft_substr(arg, s, i - s);
	if (!str)
		exit(1);
	tmp = get_form_my_env(str, env);
	free(str);
	if (!tmp)
		tmp = ft_strdup("");
	save = ft_strjoin(*ptr, tmp);
	free(tmp);
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
			|| ft_isalnum(s[0][i + 1])
			|| s[0][i + 1] == '_'))
			i = expend_var(&str, i, *s, env);
		else
		{
			join_string(&str, s[0][i]);
			i++;
		}
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
