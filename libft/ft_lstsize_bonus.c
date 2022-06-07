/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 04:51:38 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/17 20:03:41 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int main()
{
	t_list *head;
	t_list *new;
	
	head = ft_lstnew(ft_strdup("JJD"));
	head-> next = new;
	new = ft_lstnew(ft_strdup("kkkk"));

	t_list *lst = head;
	int k = ft_lstsize(lst);
	printf("%d", k);
}*/
