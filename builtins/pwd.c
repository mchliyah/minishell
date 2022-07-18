/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:23:56 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/18 21:18:14 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(t_pipe_line *p_line)
{
	t_env	*env;
	char	*path;

	env = p_line->env;
	path = get_path("PWD", env);
	printf("%s\n", path);
	g_status = 0;
}
