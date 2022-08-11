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

/*
int	expend_here_duc(char **ptr, int i, char *arg, t_env *env)
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
	if (!*ptr)
	{
		perror("NULL");
		exit(1);
	}
	return (i);
}

	{
		if (s[i] == '$' && (s[i + 1] == '?'
							|| ft_isalnum(s[i + 1])))
			i = expend_var(&str, i, s, env);
		str = join_string(str, s[i]);
		i++;
	}
	return (str);
}*/

extern int	g_status;

//char	*single_quote(char *s, int *i)
//{
//	int		st;
//	char	*ret;
//
////	(*i)++;
//	st = *i;
//	while (s[*i] && s[*i] != SINGLE_QUOTE)
//	{
//		(*i)++;
//	}
//	ret = ft_substr(s, st, *i - st);
//	return (ret);
//}

//char	*double_quote(char *s, int *i, t_env *env)
//{
//	int		st;
//	char	*ret;
//
//	(*i)++;
//	st = *i;
//	while (s[*i] && s[*i] != L_DOUBLE_QUOTE)
//		(*i)++;
//	ret = ft_substr(s, st, *i - st);
//	if (check_for_variables(ret))
//		ret = variable_expander(ret, env);
//	return (ret);
//}

char	*_string_getter(char *s, int i, t_env *env)
{
	char	*var;
	char	*tmp;
	int		st;
	char	*str;

	str = ft_strdup("");
	printf("$= %s\n", s);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '?'
				|| ft_isalnum(s[i + 1])) && s[i])
		{
			i++;
			st = i;
			if (s[(i)++] == '?')
				var = ft_itoa(g_status);
			else
			{
				if (ft_isdigit(s[i]))
					i++;
				else
				{
					while ((ft_isalnum(s[i]) || s[i] == '_') && s[i])
						i++;
				}
				tmp = ft_substr(s, st, i - st);
				var = get_form_my_env(tmp, env);
				if (!var)
					var = ft_strdup("");
			}
			str = ft_strjoin(str, var);
		}
		else
		{
			str = join_string(str, s[i]);
			i++;
		}
	}
	free(s);
	return (str);
}
