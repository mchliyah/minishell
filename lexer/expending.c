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


bool	check_for_variables(char *str)
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

/*nt	is_there_squote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == L_DOUBLE_QUOTE)
			break ;
		if (arg[i] == SINGLE_QUOTE)
			return (true);
	}
	return (false);
}

int	is_there_quote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == SINGLE_QUOTE)
			break ;
		if (arg[i] == L_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}

char	*rm_quote(char *arg, t_env *env, int state)
{
	int		i;

	i = 0;
	if (arg[i] == R_DOUBLE_QUOTE && arg[i + 1] == '$'
		&& (ft_isalnum(arg[i + 2]) || arg[i + 2] == '?'))
		return (get_variable(arg, env, state));
	else
		return (get_simple_word(arg, env, state));
}

char	*rm_squote(char *arg)
{
	char	*ptr;
	char	**str;
	int		i;

	i = 0;
	if (arg[i] == '$' && arg[i + 1] == SINGLE_QUOTE)
		i++;
	str = ft_split(arg, '\'');
	free(arg);
	arg = NULL;
	if (!str)
	{
		return (NULL);
	}
	ptr = ft_strdup("");
	if (!ptr)
		printf("a Null returned in rm squote\n");
	while (str[i])
	{
		ptr = ft_strjoin(ptr, str[i]);
		if (!ptr)
			printf("a Null returned in rm squote");
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (ptr);
}

int	expend_var(char **ptr, int i, char *arg, t_env *env)
{
	char	*tmp;
	int		s;

	if (arg[i] == '$' && (arg[i + 1] == '?'
			|| ft_isalnum(arg[i + 1])))
	{
		i++;
		s = i;
		if (ft_isdigit(arg[i]))
			i++;
		else if (arg[i] == '?') {
			arg = ft_itoa(g_status);
			arg = ft_strjoin(arg, ft_itoa(g_status));
			i++;
		}
		else
			while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
				i++;
		tmp = ft_substr(arg, s, i - s);
		if (!tmp)
			exit(1);
		printf("**%s\n", tmp);
		tmp = get_form_my_env(tmp, env);
		if (!tmp)
			tmp = ft_strdup("");
		*ptr = ft_strjoin(*ptr, tmp);
		if (!*ptr)
		{
			perror("NULL");
			exit(1);
		}
	}
	return (i);
}

char	*rm_squote(char *arg, t_env *env)
{
	char	*ptr;
	int		i;

	ptr = ft_strdup("");
	if (!ptr)
	{
		perror("malloc");
		exit(1);
	}
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$' && arg[i + 1] == SINGLE_QUOTE)
			i++;
		else if (arg[i] == '$')
			i = expend_var(&ptr, i, arg, env);
		else if (arg[i] == SINGLE_QUOTE)
		{
			i++;
			while (arg[i] != SINGLE_QUOTE && arg[i])
			{
				ptr = join_string(ptr, arg[i]);
				i++;
			}
		}
		else
			ptr = join_string(ptr, arg[i]);
	}
	return (ptr);
}*/

int	expend_var(char **ptr, int i, char *arg, t_env *env)
{
	char	*tmp;
	int		s;

	if (arg[i] == '$' && (arg[i + 1] == '?'
			|| ft_isalnum(arg[i + 1])))
	{
		i++;
		s = i;
		if (ft_isdigit(arg[i]))
			i++;
		else if (arg[i] == '?')
		{
			arg = ft_itoa(g_status);
			arg = ft_strjoin(arg, ft_itoa(g_status));
			i++;
		}
		else
			while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
				i++;
		tmp = ft_substr(arg, s, i - s);
		if (!tmp)
			exit(1);
		printf("**%s\n", tmp);
		tmp = get_form_my_env(tmp, env);
		if (!tmp)
			tmp = ft_strdup("");
		*ptr = ft_strjoin(*ptr, tmp);
		if (!*ptr)
		{
			perror("NULL");
			exit(1);
		}
	}
	return (i);
}

char	*variable_expander(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$')
		{
			expend_var(&str, i, s, env)
		}
		else
			str[i] = s[i];
		i++;
	}
}
char	*single_quote_remove(char *s, int *i)
{
	int		st;
	char	*ret;

	*i++;
	st = *i;
	while (s[*i] && s[*i] != SINGLE_QUOTE)
		*i++;
	ret = ft_substr(s, st, *i - st);
	return (ret);
}

char	*double_quote_remove(char *s, int *i)
{
	int		st;
	char	*ret;

	*i++;
	st = *i;
	while (s[*i] && s[*i] != SINGLE_QUOTE)
		*i++;
	ret = ft_substr(s, st, *i - st);
	printf("ret == %s", ret);
	if (check_for_variables(ret))
		ret = variable_expander(ret);
	return (ret);
}

char	*string_getter(char *in, int *i)
{

}

t_arg	*remove_quoted_args(t_arg *token, t_env *env)
{
	int		i;
	t_arg	*arg;

	arg = token;
	while (token)
	{
		i = 0;
		while (token->content[i])
		{
			if (token->content[i] == SINGLE_QUOTE)
				single_quote_remove(token->content, &i, env);
			else if (token->content[i] == L_DOUBLE_QUOTE)
				double_quote_remove(token->content, &i);
			else
				string_getter(token->content, &i, env);
			i++;
		}
		token = token->next;
	}
	return (arg);
}

//	{
//		if (is_there_quote(token->content))
//			token->content = rm_quote(token->content, env, 1);
//		else if (is_there_squote(token->content))
//		{
//			HERE ;
//			token->content = rm_squote(token->content, env);
//		}
//		else if (check_for_variables(token->content))
//			token->content = get_variable(token->content, env, 1);
//		printf("a--- %s\n", token->content);
