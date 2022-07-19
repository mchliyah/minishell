/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:54:34 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/18 22:42:26 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_simple_word(char *arg)
{
	char	*ptr;
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(arg, '\"');
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while (tmp[i])
	{
		ptr = ft_strjoin(ptr, tmp[i]);
		i++;
	}
	return (ptr);
}

char	*get_form_my_env(char *str, t_pipe_line *env)
{
	char	*tmp;
	t_env	*pp_env;

	pp_env = env->env;
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
char	*expend(char *str, t_pipe_line *envi)
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
				|| ft_isalnum(str[i + 1]) || ft_isalpha(i + 1)))
		{
			i++;
			s = i;
			while ((ft_isalpha(str[i]) || ft_isalnum(str[i])
					|| str[i] == '_') && str[i])
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
char	*get_variable(char *arg, t_pipe_line *env)
{
	char	*ptr;
	char	**str;
	int		i;

	i = 0;
	str = ft_split(arg, '\"');
	free(arg);
	arg = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		ptr = expend(str[i], env);
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	// printf("v = %s\n", ptr);
	free(str);
	return (ptr);
}
