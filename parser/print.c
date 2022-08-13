/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:13:31 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/13 23:48:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printing(t_list	*print)
{
	int		i;

	while (print)
	{
		i = 0;
		printf("   right cmd => %s\n", print->content->content);
		if (print->content->arg)
		{
			while (print->content->arg)
			{
				printf("arg[%d] => %s\n", i + 1, print->content->arg->content);
				print->content->arg = print->content->arg->next;
			}
		}
		print = print->next;
	}
}

void	print_tokens(t_p_line *pipeline)
{
	t_list	*print;

	while (pipeline->left_p)
	{
		print = pipeline->right;
		printf("\n_____  R PIPE____\n");
		printf("            |\n");
		printing(print);
		pipeline = pipeline->left_p;
	}
	printf("\n_____  L PIPE____\n");
	printf("            |\n");
	print = pipeline->left;
	printing(print);
}
