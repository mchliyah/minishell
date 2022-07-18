/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:54:34 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/18 21:04:08 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
 *  TODO : handle $? inside quote and if founded
 */
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
	printf("ptr %s\n", ptr);
	return (ptr);
}

char	*get_env(char *tmp, t_pipe_line *env)
{
	t_pipe_line	*pp_env;

	pp_env = env;
	while (pp_env->env->next)
	{
		if (!ft_strncmp(tmp, pp_env->env->pair->key, ft_strlen(tmp)))
			return (pp_env->env->pair->value);
		pp_env->env = pp_env->env->next;
	}
	free(tmp);
	tmp = NULL;
	return (NULL);
}

char	*get_word(char *str, int *i, char *ptr)
{
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i])
		ptr = join_string(ptr, str[*i]);
		(*i)++;
	}
	return (ptr);
}
char	*expend(char *str, t_pipe_line *envi)
{
	char	*ptr;
	int		s;
	char	*tmp;
	int		i;

	i = 0;
	printf("str = == %s\n", str);
	ptr = ft_strdup("");
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			s = i;
			while ((ft_isalpha(str[i]) || ft_isalnum(str[i])
					|| str[i] == '_') && str[i])
				i++;
			tmp = ft_substr(str, s, i - s);
			printf("tmp %s\n", tmp);
			if (!tmp)
				return (NULL);
			tmp = get_env(tmp, envi);
			ptr = ft_strjoin(ptr, tmp);
			free(tmp);
			tmp = NULL;
		}
		else
			get_word(str, &i, ptr);
	}
	printf("ptr=%s\n", ptr);
	return (ptr);
}

/*
 	? the variable stops when he found space or anything else
 	? not letter or underscore (-) or number
 	? means that underscore and number
 */
char	*get_variable(char *arg, t_pipe_line *env)
{
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
		expend(str[i], env);
		i++;
	}
	return NULL;
}