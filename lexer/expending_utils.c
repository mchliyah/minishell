/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:54:34 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/19 13:11:46 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_simple_word(char *arg, t_env *env)
{
	char	*ptr;
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = ft_split(arg, '\"');
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == '$' && tmp[i + 1] == NULL)
			{
				ptr = ft_strjoin(ptr, get_variable(&tmp[i][j], env));
				free(tmp[i]);
				free(tmp);
				return (ptr);
			}
			ptr = join_string(ptr, tmp[i][j]);
			j++;
		}
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (ptr);
}

char	*get_form_my_env(char *str, t_env *env)
{
	char	*tmp;
	t_env	*pp_env;

	pp_env = env;
	tmp = ft_strjoin(str, "=");
	free(str);
	while (pp_env->next)
	{
		if (!ft_strncmp(tmp, pp_env->pair->key, ft_strlen(pp_env->pair->key)))
		{
			free(tmp);
			tmp = NULL;
			return (pp_env->pair->value);
		}
		pp_env = pp_env->next;
	}
	return (NULL);
}

char	*get_word(char *str, int *i, char *ptr)
{
	while (str[*i])
	{
		if (str[*i] == '$' && (str[*i + 1] == '?'
				|| ft_isalnum(str[*i + 1]) || ft_isalpha(*i + 1)))
			break ;
		ptr = join_string(ptr, str[*i]);
		(*i)++;
	}
	return (ptr);
}

/*
 *  TODO : handle $? inside quote and if founded
 */
char	*expend(char *str, t_env *envi)
{
	char	*ptr;
	int		s;
	char	*tmp;
	int		i;

	i = 0;
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '?'
				|| ft_isalnum(str[i + 1])))
		{
			i++;
			s = i;
			if (ft_isdigit(str[i]))
				i++;
			else if (str[i] == '?')
			{
				ptr = ft_strjoin(ptr, ft_itoa(g_status));
				i++;
			}
			else
				while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
					i++;
			tmp = ft_substr(str, s, i - s);
			if (!tmp)
				return (NULL);
			tmp = get_form_my_env(tmp, envi);
			if (!tmp)
				tmp = ft_strdup("");
			ptr = ft_strjoin(ptr, tmp);
		}
		else
			ptr = get_word(str, &i, ptr);
	}
	return (ptr);
}

/*
 	? the variable stops when he found space or anything else
 	? not letter or underscore (-) or number
 	? means that underscore and number
 */
char	*get_variable(char *arg, t_env *env)
{
	char	*ptr;
	char	**str;
	int		i;

	i = 0;
	str = ft_split(arg, '\"');
	if (!str)
		return (NULL);
	while (str[i])
	{
		ptr = expend(str[i], env);
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (ptr);
}
