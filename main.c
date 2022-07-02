/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/02 22:41:44 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_pipe_line	*pipeline;
	int			i;
	char		*str_rln;

	(void)ac;
	(void)av;
	i = 0;
	pipeline = malloc(sizeof(t_pipe_line));
	env_init(pipeline, env);
	while (1)
	{
		str_rln = readline("✅ minishell 🤬🤬🤬🤬➡️");
		if (!str_rln)
			break ;
		add_history(str_rln);
		generate_token(str_rln, pipeline);
	}
	return (0);
}
