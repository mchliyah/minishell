/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/08 01:57:33 by mchliyah         ###   ########.fr       */
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

void	add_elem(t_env **env, t_pair *to_exp, int exist)
{
	t_env	*tmp;

	tmp = *env;
	if (!exist)
	{
			HERE;
		while (tmp)
		{
			if (!strncmp(tmp->pair->key, to_exp->key,
					ft_strlen(tmp->pair->key)))
			{
				free(tmp->pair->value);
				tmp->pair->value = NULL;
				if (to_exp->value)
					tmp->pair->value = ft_strdup(to_exp->value);
				return ;
			}
			tmp = tmp->next;
		}
			HERE;
		tmp = dup_not_exist_elem(to_exp);
		tmp->next = NULL;
	}
	else
		dup_exist_elem(&tmp, to_exp);
}

void	export_elem(t_list *cmd, t_pair *to_exp, t_env **dynamic_env)
{
	int	add;

	HERE;
	add = ft_strlen(ft_strchr(to_exp->key, '+'));
	if (add)
	{
		to_exp->key[ft_strlen(to_exp->key) - 1] = '\0';
		PV(to_exp->key, " in the add elem %s\n");
		add_elem(dynamic_env, to_exp, 1);
	}
	else
		add_elem(dynamic_env, to_exp, 0);
	print_exp((*dynamic_env));
}

int	valide(t_pair *to_exp)
{
	if (to_exp->value)
		return (1);
	return (0);
}

void	check_add(t_list *c_line, char *args, t_env **exp, t_env **env)
{
	int		ret;
	t_pair	*to_exp;
	int		len;
	int		len_max;

	len_max = ft_strlen(args);
	to_exp = malloc(sizeof(t_pair));
	len = ft_strlen(ft_strchr(args, '='));
	to_exp->value = NULL;
	to_exp->key = ft_substr(args, 0, len_max - len);
	if (len)
		to_exp->value = ft_substr(args, len_max - len + 1, len_max);
	ret = check_exp(to_exp->key);
	if (ret < 0)
		exp_error(ret, args);
	else
	{
		if (valide(to_exp))
		{
			HERE;
			export_elem(c_line, to_exp, exp);
			if (to_exp->value[0] != '\0')
				export_elem(c_line, to_exp, env);
		}
		else
			export_elem(c_line, to_exp, exp);
	}
}

void	export_cmd(t_data **data, t_list *c_line)
{
	char	**args;
	t_env	*expt;
	t_env	*envp;
	int		i;

	i = 1;
	expt = (*data)->exp;
	envp = (*data)->env;
	if (!c_line->content->arg)
		print_exp((*data)->exp);
	else
	{
		args = arr_arg(c_line);
		while (expt->next)
			expt = expt->next;
		while (envp->next)
			envp = envp->next;
		while (args[i])
		{
			check_add(c_line, args[i], &expt, &envp);
			i++;
		}
		free (args);
	}
	sort_exp(&(*data)->exp);
}
