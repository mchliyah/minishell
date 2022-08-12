/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:23:56 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/12 22:20:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(t_env	*env)
{
	(void)env;
	char *pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
		pwd = get_path("PWD", env);
	if (pwd)
		printf("%s\n", pwd);
}
