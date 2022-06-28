/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:13:31 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/27 23:04:17 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	print_tokens(t_pipe_line *pipeline)
{
	int		i;
	t_list	*print;

	while (pipeline)
	{
		printf("\n_____  R PIPE____\n");
		printf("            |\n");
		print = pipeline->right;
		while (print)
		{
			i = -1;
			printf("   right cmd => %s\n", print->content->content);
			if (print->content->args)
				while (print->content->args[++i])
					printf("arg[%d] => %s\n", i + 1, print->content->args[i]);
			print = print->next;
		}
		if (pipeline->left)
		{
			print = pipeline->left;
			printf("\n_____  L PIPE____\n");
			printf("            |\n");
			while (print)
			{
				i = -1;
				printf("left cmd => %s\n", print->content->content);
				if (print->content->args)
					while (print->content->args[++i])
						printf("arg[%d] => %s\n", i + 1, print->content->args[i]);
				print = print->next;
			}
		}
		pipeline = pipeline->left_p;
	}
}