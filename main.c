/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/07/19 13:08:34 by mchliyah         ###   ########.fr       */
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
		free(pipeline->right->content->args);
		free(pipeline->right->content->content);
		free(pipeline->right->content);
		free(pipeline->right);
	}
	if (pipeline->left)
	{
		free(pipeline->left->content->args);
		free(pipeline->left->content->content);
		free(pipeline->left->content);
		free(pipeline->left);
	}
}

// int	init_mini(t_pipe_line *pipeline, t_env *env)
// {
	
// }

int	main(int ac, char **av, char **envp)
{
	t_pipe_line	*pipeline;
	t_env		*env;
	char		*str_rln;

	(void)ac;
	(void)av;
	g_status = 0;
	pipeline = malloc(sizeof(t_pipe_line));
	pipeline->exit = 0;
	env = env_init(envp);
	while (!pipeline->exit)
	{
		str_rln = readline("✅ minishell 🤬➡️");
		if (!str_rln)
			break ;
		if (*str_rln)
		{
			add_history(str_rln);
			generate_token(str_rln, pipeline, env);
			exec_cmd(pipeline, env);
			// printf("%p\n", pipeli);
			to_free(pipeline);
		}
	}
	return (g_status);
}
