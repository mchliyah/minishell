/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/01 23:18:57 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exp(t_env *exp)
{
	while (exp)
	{
		printf("declare -x %s", exp->pair->key);
		if (exp->pair->value)
			printf("=\"%s\"\n", exp->pair->value);
		else
			printf("\n");
		exp = exp->next;
	}
}

void	add_elem(t_env **env, char *str, int exist)
{
	t_env	*tmp;

	tmp = *env;
	if (!exist)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_env));
		tmp->next->next = NULL;
		tmp->next->pair = malloc(sizeof(t_pair));
		if (tmp->next)
			tmp->next = dup_not_exist_elem(tmp->next, str);
	}
	else
		dup_exist_elem(tmp, str);
}

void	export_elem(int ret, t_list *cmd, char *arg, t_env **exp, t_env **env)
{
	if (!ret)
		add_elem(exp, arg, 0);
	else
	{
		if (ret == 1)
		{
			if (elem_exist(*exp, arg))
				unset_cmd(exp, cmd);
			add_elem(exp, arg, 0);
			if (elem_exist(*env, arg))
				unset_cmd(env, cmd);
			add_elem(env, arg, 0);
		}
		else
		{
			if (elem_exist(*exp, arg))
				add_elem(exp, arg, 1);
			else
				add_elem(exp, arg, 0);
			if (elem_exist(*env, arg))
				add_elem(env, arg, 1);
			else
				add_elem(env, arg, 0);
		}
	}
}

void	check_add(t_list *c_line, char *args, t_env **exp, t_env **env)
{
	int		ret;

	ret = 0;
	ret = check_exp(args);
	if (ret < 0)
		exp_error(ret, args);
	else
		export_elem(ret, c_line, args, exp, env);
}

void	export_cmd(t_env **exp, t_env **env, t_list *c_line)
{
	char	**args;
	t_env	*expt;
	t_env	*envp;
	int		i;

	i = 1;
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
			check_add(c_line, args[i], exp, env);
			i++;
		}
		free (args);
	}
	sort_exp(exp);
}
