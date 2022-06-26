/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/26 14:17:56 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*str_rln;

	while (1)
	{
		str_rln = readline("✅ minishell ➡️");
		if (!str_rln)
			return (1);
		if (*str_rln)
			add_history(str_rln);
		generate_token(str_rln);
	}
	return (0);
}
