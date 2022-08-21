/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_holder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:40:06 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/21 09:40:08 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_string(char **ptr, char c)
{
	char	*j_str;
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		exit(1);
	ft_bzero(str, 2);
	str[0] = c;
	j_str = ft_strjoin(*ptr, str);
	if (!j_str)
		exit(1);
	free(str);
	free(*ptr);
	*ptr = j_str;
}

bool	check_spectial_char(t_lexer **lex)
{
	if (ft_isprint((*lex)->content[(*lex)->i + 1])
		&& (*lex)->content[(*lex)->i + 1] != EPIPE
		&& (*lex)->content[(*lex)->i + 1] != LESS
		&& (*lex)->content[(*lex)->i + 1] != GREATER
		&& (*lex)->content[(*lex)->i + 1] != SPACE)
		return (true);
	return (false);
}

bool	ft_space_advacer(t_lexer **lex)
{
	if ((*lex)->c == SPACE)
	{
		while ((*lex)->c == SPACE)
			*lex = advance(*lex);
		if ((*lex)->c == EOS)
			return (false);
	}
	return (true);
}

void	ft_single(t_lexer **lex, char **ptr)
{
	char	*save;
	char	*tmp;

	*lex = advance(*lex);
	save = get_s_quote_things(lex);
	tmp = ft_strjoin(*ptr, save);
	free_strjoin(ptr, &save);
	*ptr = tmp;
}
