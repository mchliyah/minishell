/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/01 13:56:05 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exp(t_env *exp)
{
	while (exp)
	{
		printf("declare -x %s=\"%s\"\n", exp->pair->key, exp->pair->value);
		exp = exp->next;
	}
}

void	add_elem(t_env **env, char *str, int exist)
{
	int		i;
	int		j;
	t_env	*tm;
	char	*value;

	j = 0;
	i = 0;
	value = NULL;
	tm = *env;
	if (!exist)
	{
		while (tm->next)
			tm = tm->next;
		tm->next = malloc(sizeof(t_env));
		tm->next->next = NULL;
		tm->next->pair = malloc(sizeof(t_pair));
		if (tm->next)
		{
			while (str[i] && str[i] != '=')
				i++;
			if (str[i - 1] == '+')
				tm->next->pair->key = env_dup(str, i - 1, j);
			else
				tm->next->pair->key = env_dup(str, i, j);
			j = ++i;
			while (str[i])
				i++;
			tm->next->pair->value = env_dup(str, i, j);
		}
	}
	else
	{
		while (str[i] != '=')
			i++;
		j = ++i;
		while (str[j])
			j++;
		value = env_dup(str, i, j);
		while (tm)
		{
			if (!strncmp(tm->pair->key, &str[i], ft_strlen(tm->pair->key)))
				tm->pair->value = ft_strjoin(tm->pair->key, value);
			tm = tm->next;
		}
		free(value);
	}
}

void	export_elem(int ret, t_list *cmd, char *arg, t_env **exp, t_env **env)
{
	if (!ret)
		add_elem(exp, arg, 0);
	else
	{
		if (ret == 1)
		{
			if (exist(*exp, arg))
				add_elem(exp, arg, 1);
			else
				add_elem(exp, arg, 0);
			if (exist(*env, arg))
				add_elem(env, arg, 1);
			else
				add_elem(env, arg, 0);
		}
		else
		{
			unset_cmd(exp, cmd);
			add_elem(exp, arg, 0);
			unset_cmd(env, cmd);
			add_elem(env, arg, 0);
		}
	}
}

void	export_cmd(t_env **exp, t_env **env, t_list *c_line)
{
	char	**args;
	t_env	*expt;
	t_env	*envp;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	expt = *exp;
	envp = *env;
	if (!c_line->content->arg)
		print_exp(*exp);
	else
	{
		args = arr_arg(c_line);
		while (expt->next)
			expt = expt->next;
		while (envp->next)
			envp = envp->next;
		while (args[i])
		{
			ret = check_exp(args[i]);
			if (ret < 0)
				exp_error(ret, args[i]);
			else
				export_elem(ret, c_line, args[i], &expt, &envp);
			i++;
		}
		free (args);
	}
	sort_exp(exp);
}
