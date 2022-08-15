/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:57:26 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/13 23:48:11 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

	/*
	 *  left    output to 1   |_0_|_1_|
	 *  right input form 0 and output to 1 if there is no out redirection
	 *
	 *   cmd[0]    |  cmd[1]   |   cmd[2]
	 *   |_x_|_1_| - |_0_|_3_| - |_x_|_2_|
	 *  4          2
	 */

int	execute_childes(t_p_line *this_pipe, t_data **data)
{
	if (this_pipe->left)
		exec_cmd(this_pipe->left, data);
	if (this_pipe->right)
	{
		(*data)->cmd_i++;
		(*data)->p_in += 2;
		exec_cmd(this_pipe->right, data);
	}
	return (0);
}

int	iterator(t_p_line *this_pipe, t_data **data)
{
	if (this_pipe->left_p)
		iterator(this_pipe->left_p, data);
	execute_childes(this_pipe, data);
	return (EXIT_SUCCESS);
}
