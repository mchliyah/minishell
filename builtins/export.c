/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:26:45 by mchliyah          #+#    #+#             */
/*   Updated: 2022/07/21 18:07:44 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void print(t_env *export)
{
    while (export)
    {
        /* code */
    }
    
}

void    export_cmd(t_env *export, t_list *c_line)
{
    if (!c_line->content->args[0])
    {
        print(export);
        return (0);
    }
    else
    {
        while(export->next)
            export = export->next;
        export->next = malloc(sizeof(t_env));
        export->next->pair->key = ft_strdup(c_line->content->content);
        export->next->pair->value = ft_strdup(c_line->content->args[0]);
        


    }
}