/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:23:56 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/20 23:42:25 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	pwd_cmd(t_env	*env)
{
	char	*pwd;
	int		must_free;

	must_free = 0;
	pwd = get_path("PWD", env);
	if (!pwd)
	{
		pwd = getcwd(NULL, 1024);
		must_free = 1;
	}
	if (pwd)
	{
		printf("%s\n", pwd);
		if (must_free)
			free(pwd);
	}
	g_status = 0;
}
