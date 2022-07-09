/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/04 15:47:48 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_pipe_line	*pipeline;
	//int			i;
	char		*str_rln;

	(void)ac;
	(void)av;
//	i = 0;
	pipeline = malloc(sizeof(t_pipe_line));
	if (env_init(pipeline, env))
	{
		while (1)
		{
			str_rln = readline("✅ minishell 🤬🤬🤬🤬➡️");
			if (!str_rln) {
				break ;
			}
			if (*str_rln)
			{
				add_history(str_rln);
				// if you want to add function under this function
				// you should add a condition for it
				// !! if (generate... != 1) then do what you want
				// else if generate .. == 1 means that there is unclosed
				//	quote or single quote !!
				generate_token(str_rln, pipeline, env);
			}
		}
	}
	return (0);
}
