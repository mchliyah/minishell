/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:02:43 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/17 04:51:07 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

//int main()
//{
//	t_list *head;
//	head = ft_lstnew(ft_strdup("hello"));
//	t_list *lst = head;
//	t_list *nec;
//	nec = ft_lstnew(ft_strdup("he "));
//	ft_lstadd_front(&lst, nec);
//	while(lst != NULL)
//	{
//		printf("%s", lst->content);
//		lst = lst->next;
//	}
//}
