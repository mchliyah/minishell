/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/09 01:02:42 by mchliyah         ###   ########.fr       */
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

int	valide(t_pair *to_exp)
{
	if (to_exp->value)
		return (1);
	return (0);
}

void	export_elem(t_pair *to_exp, t_env **exp, t_env **env)
{
	int		add;

	add = 0;
	if (valide(to_exp))
	{
		add = ft_strlen(ft_strchr(to_exp->key, '+'));
		if (add)
			to_exp->key[ft_strlen(to_exp->key) - 1] = '\0';
		add_elem(exp, to_exp, add);
		if (to_exp->value[0] != '\0')
			add_elem(env, to_exp, add);
	}
	else
		add_elem(exp, to_exp, 0);
}

void	check_add(char *args, t_env **exp, t_env **env)
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
		export_elem(to_exp, exp, env);
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
		while (args[i])
		{
			check_add(args[i], &expt, &envp);
			i++;
		}
		free (args);
	}
	sort_exp(&expt);
}
