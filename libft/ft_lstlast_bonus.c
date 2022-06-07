/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:01:40 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/27 19:12:49 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
//int main()
//{
//    t_list *head;
//    t_list *lst;
//    head = ft_lstnew("hhdo");
//    lst = head;
//    head->next = ft_lstnew(" kilo");
//    t_list *last;
//    last = ft_lstlast(lst);
//    printf("%s", last->content);
//}
