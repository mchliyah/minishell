/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:37 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/18 17:43:29 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    exit_cmd(t_list *c_line)
{
    char *args0;

    args0 = c_line->content->args[0];
    ft_putstr_fd("exit", 2);
    if (args0 && c_line->content->args[1])
    {
        g_status = 1;
        ft_putchar_fd("minishell: exit: arguments error", 2);
    }
    else if (args0 && !ft_isalnum(args0))
    {
        g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args0, 2);
		ft_putendl_fd(": put numiric arg", 2);
    }
    else if (args0)
        g_status = ft_atoi(args0);
}