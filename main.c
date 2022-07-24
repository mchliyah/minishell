/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/24 22:56:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
  ?? this comments for anything under generate_token function !!
 	if you want to add function under this function
 	you should add a condition for it
 	!! if (generate... != 1) then do what you want
 	else if generate .. == 1 means that there is unclosed
	quote or single quote !!
 */

void	to_free(t_pipe_line *pipeline)
{
	while (pipeline->left_p)
	{
		free(pipeline->right->content);
		free(pipeline->right);
		pipeline = pipeline->left_p;
	}
	if (pipeline->right)
	{
		free(pipeline->right->content->arg);
		free(pipeline->right->content->content);
		free(pipeline->right->content);
		free(pipeline->right);
	}
	if (pipeline->left)
	{
		free(pipeline->left->content->arg);
		free(pipeline->left->content->content);
		free(pipeline->left->content);
		free(pipeline->left);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe_line	*pipeline;
	t_env		*env;
	t_env		*exp;
	char		*str_rln;

	(void)ac;
	(void)av;
	pipeline = malloc(sizeof(t_pipe_line));
	pipeline->exit = 0;
	env = env_init(envp);
	exp = env_init(envp);
	while (!pipeline->exit)
	{
		str_rln = readline("\033[1;31m ~minishell~: \033[0m");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
			add_history(str_rln);
			generate_token(str_rln, pipeline, env);
			exec_cmd(pipeline, env, envp);
			to_free(pipeline);
			if (generate_token(str_rln, pipeline, env) != 1)
			{
				exec_cmd(pipeline, env, envp);
				to_free(pipeline);
			}
		}
	}
	printf("exit\n");
	return (g_status);
}
