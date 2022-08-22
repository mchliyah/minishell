/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:59:58 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/11 18:00:00 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	*get_alnum(char *s, int *i, t_env *env)
{
	char	*var;
	int		st;
	char	*tmp;

	st = *i;
	if (ft_isdigit(s[(*i)]))
		(*i)++;
	else
	{
		while ((ft_isalnum(s[(*i)]) || s[(*i)] == '_') && s[(*i)])
			(*i)++;
	}
	tmp = ft_substr(s, st, *i - st);
	var = get_form_my_env(tmp, env);
	if (!var)
		var = ft_strdup("");
	free(tmp);
	return (var);
}

void	ft_h_string_getter_helper(char *s, int *i, t_env *env, char **str)
{
	char	*status;
	char	*tmp;

	if (s[*i] == '?')
	{
		status = ft_itoa(g_status);
		tmp = ft_strjoin(*str, status);
		free(status);
		status = NULL;
		(*i)++;
	}
	else
		tmp = ft_strjoin(*str, get_alnum(s, i, env));
	free(*str);
	*str = tmp;
}

char	*h_string_getter(char *s, int i, t_env *env)
{
	char	*str;

	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '?'
				|| ft_isalnum(s[i + 1])
				|| s[i + 1] == '_') && s[i])
		{
			i++;
			ft_h_string_getter_helper(s, &i, env, &str);
		}
		else
		{
			join_string(&str, s[i]);
			i++;
		}
	}
	free(s);
	return (str);
}
