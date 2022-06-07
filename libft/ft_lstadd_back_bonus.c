/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:01:16 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/27 19:13:53 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	ft_lstlast(*lst)->next = new;
}
//int main()
//{
//    t_list *last;
//    last = ft_lstnew(0);
//    ft_lstadd_back(&last,ft_lstnew(ft_strdup("hello")));
//    ft_lstadd_back(&last, ft_lstnew(ft_strdup("12")));
//    ft_lstadd_back(&last, ft_lstnew(ft_strdup("34")));
//    //printf("%s", (char *)last->content);
//   while (last != 0)
//    {
//        printf("    -%s", (char *)last->content);
//        last = last->next;
//    }
//    //printf("%s", last->content);
//}
