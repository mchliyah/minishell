/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/30 15:15:03 by mchliyah         ###   ########.fr       */
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

void	exp_error(int ret, char *str)
{
	if (ret == -1)
	{
		write (2, "export : ", 10);
		write (2, &str, 2);
		write (2, "invalid option\n", 16);
	}
	else
	{
		ft_putstr_fd(2, "export : ");
		ft_putstr_fd(2, str);
		ft_putstr_fd(2, ": not a valid identifier\n");
	}
}

t_env	*add_elem(t_env *env, char *str, int exist)
{
	int		i;
	int		j;
	t_env	*tm;
	char	*value;

	j = 0;
	i = 0;
	value = NULL;
	tm = env;
	if (!exist)
	{
		while (tm->next)
			tm = tm->next;
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
			if (!strncmp(tm->pair->key, str[i], ft_strlen(tm->pair->key)))
				tm->pair->value = ft_strjoin(tm->pair->key, value);
			tm = tm->next;
		}
		free(value);
	}
	return (env);

}

void	export_elem(int ret, char arg, t_env **exp, t_env **env)
{
	if (!ret)
		exp = add_elem(exp, arg, 0);
	else
	{
		if (ret == 1)
		{
			if (exist(exp, arg))
				exp = add_elem(exp, arg, 1);
			else
				exp = add_elem(exp, arg, 0);
		}
		else
			exp = add_elem(exp, arg, 0);
	}
}

void	export_cmd(t_env **exp, t_env **env, t_list *c_line)
{
	char	**args;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!c_line->content->arg)
		print_exp(*exp);
	else
	{
		args = arr_arg(c_line);
		while ((*exp)->next)
			*exp = (*exp)->next;
		while (args[i])
		{
			ret = check_exp(args[i]);
			if (ret < 0)
				exp_error(ret, args[i]);
			else
				export_elem(ret, args[i], exp, env);
			i++;
		}
		free (args);
	}
}
