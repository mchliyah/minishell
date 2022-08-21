/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:22:00 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 19:37:50 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_status;

void	main_parent_waiting(int count, t_data **data)
{
	int		i;

	i = 0;
	while (i < (*data)->pip_nb * 2)
		close((*data)->p_fd[i++]);
	i = -1;
	while (++i < count)
	{
		close((*data)->here_fd[i][0]);
		close((*data)->here_fd[i][1]);
	}
}

void	parser_main(char *str_rln, t_data **data)
{
	t_p_line	*pipeline;

	while (!(*data)->exit)
	{
		str_rln = readline("~mi🙂nish🙂ell:~ ");
		if (!str_rln)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		pipeline = malloc(sizeof(t_p_line));
		if (*str_rln)
		{
			get_tkn_exec(str_rln, data, &pipeline);
			free_list((*data)->lst_tok);
		}
		else if (*str_rln == '\0')
			g_status = 0;
		free(pipeline);
		pipeline = NULL;
		free(str_rln);
	}
}
