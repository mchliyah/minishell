/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/01 14:13:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_pipeline	*pipeline;
	char	*str_rln;

	(void)ac;
	(void)av;

	pipeline = malloc(sizeof(t_pipe_line));
	init_env(pipeline, env);
	while (1)
	{
		str_rln = readline("✅ minishell ➡️");
		if (!str_rln)
			break ;
		add_history(str_rln);
		generate_token(str_rln, pipeline);
	}
	return (0);
}
