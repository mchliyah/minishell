/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:54:34 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/09 20:11:53 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

char	*get_simple_word(char *arg, t_env *env, int state)
{
	int		start;
	char	*sub;
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
				ptr = ft_strjoin(ptr, get_variable(&tmp[i][j], env, state));
				free(tmp[i]);
				free(tmp);
				return (ptr);
			}
			if (tmp[i][j] == '$' && (ft_isalnum(tmp[i][j + 1])
				|| tmp[i][j + 1] == '_'))
			{
				if (ft_isdigit(tmp[i][j + 1]))
				{
					sub = ft_substr(tmp[i], j, 2);
					ptr = get_variable(sub, env, state);
				}
				else
				{
					start = j;
					while (tmp[i][j])
					{
						j++;
						if (((tmp[i][j] == '$' || tmp[i][j] == L_DOUBLE_QUOTE
							|| tmp[i][j] == SINGLE_QUOTE)
							|| (!ft_isalnum(tmp[i][j]))) && tmp[i][j] != '_')
						{
							sub = ft_substr(tmp[i], start, j - start);
							ptr = ft_strjoin(ptr,
									get_variable(sub, env, state));
							free(sub);
							start = j;
						}
					}
				}
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

char	*get_form_my_env(char *tmp, t_env *env)
{
	t_env	*pp_env;

	pp_env = env;
	while (pp_env->next)
	{
        if (!ft_strcmp(tmp, pp_env->pair->key))
		{
			free(tmp);
			tmp = NULL;
			return (pp_env->pair->value);
		}
		pp_env = pp_env->next;
	}
	free(tmp);
	tmp = NULL;
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
char	*expend(char *str, t_env *envi, int state)
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
			printf("tmp = %s\n", tmp);
			tmp = get_form_my_env(tmp, envi);
			if (!tmp && state == 1)
				tmp = ft_strdup("");
			else if (!tmp && state == 0)
				return (NULL);
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
 	! state 1 for args
 	! state 0 for cmd
 */
char	*get_variable(char *arg, t_env *env, int state)
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
		ptr = expend(str[i], env, state);
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (ptr);
}
