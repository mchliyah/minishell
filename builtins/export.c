/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 22:04:54 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_exp(t_env **exp)
{
	t_env	*tmp;
	t_env	*tmp1;
	t_pair	*pair;

	if (exp)
	{
		tmp = *exp;
		while (tmp->next)
		{
			tmp1 = tmp->next;
			while (tmp1)
			{
				if (ft_strcmp(tmp->pair->key, tmp1->pair->key) > 0)
				{
					pair = tmp->pair;
					tmp->pair = tmp1->pair;
					tmp1->pair = pair;
				}
				tmp1 = tmp1->next;
			}
			tmp = tmp->next;
		}
	}
}

int	check_exp(char *str)
{
	int	i;

	i = 0;
	if (str[0])
		return (-2);
	if ((str[0] < 'a' || str[0] >'z') && (str[0] < 'A' || str[0] > 'Z')
		&& str[0] != '_' )
		return (-1);
	while(str[i])
	{
		if(str[i] == '-')
			return (-2);
		else
		{
			if (str[i] == '=' && str[i - 1] != '+')
				return (1);
			else if (str[i] == '=' && str[i - 1] == '+')
				return (2);
		}
		i++;
	}
	return (0);	
}

t_env	*add_elem(t_env *env, char *str, int exist)
{
	int 	i;
	int		j;
	t_env	*tm;
	char	*value;

	j = 0;
	i = 0;
	value = NULL;
	tm = env;
	if (!exist)
	{
		while(tm->next)
			tm = tm->next;
		tm->next->pair = malloc(sizeof(t_pair))
		if (tm->next)
		{
			while(str[i] && str[i] != '=')
				i++;
			if (str[i - 1] == '+')
				tm->next->pair->key = env_dup(tmp_val, i - 1, j);
			esle
				tm->next->pair->key = env_dup(tmp_val, i, j);
			j = ++i;
			while(str[i])
				i++;
			tm->next->pair->value = env_dup(tmp_val, i, j);
		}

	}
	esle
	{
		while(str[i] != '=')
			i++;
		j = ++i;
		while (str[j])
			j++; 
		value = env_dup(str, i, j);
		while (tm)
		{
			if (!strncmp(tm->pair->key), str[i], ft_strlen(tm->pair->key))
				tmp->pair->value = ft_strjoin(tm->pair->key, value);
			tm = tm->next;
		}
		free(value);
	}
	return (env);

}

int exist(t_env *env, char *arg)
{
	int	i = 0;
	while(arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		i--
	while(env)
	{
		if (!strncmp(env->pair->key, arg, i))
			return (1);
		env = env->next;
	}
	return (0);
}

void	export_cmd(t_env **exp, t_env **env, t_list *c_line)
{
	char	**args;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!c_line->content->arg)
	{
		print_exp(*exp);
		return ;
	}
	else
	{
		args = arr_arg(c_line);
		while ((*exp)->next)
			*exp = (*exp)->next;
		while (args[i])
		{
			ret = check_exp(arg[i]);
			if (ret < 0)
				exp_error(ret, arg[i]);
			else
			{
				if (!ret)
					exp = add_elem(exp, arg[i], 0);
				else
				{
					if (ret == 1)
					{
						if (exist(exp, arg[i]))
							exp = add_elem(exp, arg[i], 1);
						else
							exp = add_elem(exp, arg[i], 0);

					}
					else
						exp = add_elem(exp, arg[i], 0);

				}
			}
			i++;
		}
		free (args);
	}
}

void	print_exp(t_env *exp)
{
	while (exp)
	{
		printf("declare -x %s=\"%s\"\n", exp->pair->key, exp->pair->value);
		exp = exp->next;
	}
}