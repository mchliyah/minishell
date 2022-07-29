/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:23:56 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/28 12:21:21 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(t_env	**env)
{
	char	*path;

	path = get_path("PWD", *env);
	if (path)
		printf("%s\n", path);
	// g_status = 0;
}
