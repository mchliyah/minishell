/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:44:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/27 23:01:33 by mchliyah         ###   ########.fr       */
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
			break ;
		add_history(str_rln);
		generate_token(str_rln);
	}
	return (0);
}
