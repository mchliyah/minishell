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

void	print_exp(t_env *exp)
{
	while (exp)
	{
		printf("declare -x %s=\"%s\"\n", exp->pair->key, exp->pair->value);
		exp = exp->next;
	}
}

int	check_exp(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i + 1] && str[i] == '+' && str[i + 1] == '=')
	}
	
}

t_env 

void	export_cmd(t_env **exp, t_list *c_line)
{
	char	**args;
	int		i;

	i = 1;
	if (!c_line->content->arg)
	{
		print_exp(*exp);
		return ;
	}
	else
	{
		args = arr_arg(c_line);
		// for (int i = 1;  args[i]; i++)
		// 	printf("%s\n", args[i]);
		while ((*exp)->next)
			*exp = (*exp)->next;
		while (args[i])
		{
			if (check_exp = )
			i++;
		}
		*exp = add_elem();
		(*exp)->next = malloc(sizeof(t_env));
		(*exp)->next->pair = malloc(sizeof(t_pair));
		(*exp)->next->pair->key = ft_strdup(args[0]);
		(*exp)->next->pair->value = ft_strdup(args[1]);
		(*exp)->next->next = NULL;
		free (args);
	}
}
