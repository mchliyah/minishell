/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:13:31 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/28 19:46:10 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printing(t_list	*print)
{
	int		i;

	while (print)
	{
		i = -1;
		printf("   right cmd => %s\n", print->content->content);
		if (print->content->arg->content)
			while (print->content->arg->content[++i])
				printf("arg[%d] => %s\n", i + 1, print->content->arg->content);
		print = print->next;
	}
}

void	print_tokens(t_pipe_line *pipeline)
{
	t_list	*print;

	while (pipeline)
	{
		printf("\n_____  R PIPE____\n");
		printf("            |\n");
		print = pipeline->right;
		printing(print);
		if (pipeline->left)
		{
			print = pipeline->left;
			printf("\n_____  L PIPE____\n");
			printf("            |\n");
			printing(print);
		}
		pipeline = pipeline->left_p;
	}
}
