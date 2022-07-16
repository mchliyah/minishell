/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:54:34 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/15 14:54:36 by ael-mous         ###   ########.fr       */
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
	printf("ptr %s\n", ptr);
	return (ptr);
}

char	*get_env(char *tmp, t_pipe_line *pp_env)
{
	while (pp_env->env->next)
	{
		if (!ft_strncmp(tmp, pp_env->env->pair->key, ft_strlen(tmp)))
			return (pp_env->env->pair->value);
		pp_env->env = pp_env->env->next;
	}
	return (NULL);
}

char	*expend(char *str, t_pipe_line *env)
{
	char	*tmp;
	int		s;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			s = i;
			while (ft_isalpha(str[i]) || ft_isalnum(str[i])
				|| str[i] == '_' || str[i])
				i++;
			tmp = ft_substr(str, s, i - s - 1);
			printf("tmp %s\n", tmp);
			if (!tmp)
				return NULL;
			printf("variable === %s\n", get_env(tmp, env));
		}
	}
	return tmp;
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