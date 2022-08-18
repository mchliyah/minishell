/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expending_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:59:58 by ael-mous          #+#    #+#             */
/*   Updated: 2022/08/11 18:00:00 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	*h_string_getter(char *s, int i, t_env *env)
{
	char	*var;
	char	*tmp;
	int		st;
	char	*str;

	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '?'
				|| ft_isalnum(s[i + 1])) && s[i])
		{
			i++;
			st = i;
			if (s[(i)++] == '?')
				var = ft_itoa(g_status);
			else
			{
				if (ft_isdigit(s[i]))
					i++;
				else
				{
					while ((ft_isalnum(s[i]) || s[i] == '_') && s[i])
						i++;
				}
				tmp = ft_substr(s, st, i - st);
				var = get_form_my_env(tmp, env);
				if (!var)
					var = ft_strdup("");
			}
			str = ft_strjoin(str, var);
		}
		else
		{
			join_string(&str, s[i]);
			i++;
		}
	}
	free(s);
	return (str);
}
