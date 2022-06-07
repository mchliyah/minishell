/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:20:49 by ael-mous          #+#    #+#             */
/*   Updated: 2021/11/17 20:02:52 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*newc;

	newc = NULL;
	newc = (t_list *)malloc(sizeof (t_list));
	if (!newc)
		return (NULL);
	newc->content = content;
	newc->next = NULL;
	return (newc);
}
/*
int main()
{
	//int i[] = {1, 2, 3, 4, 5};
	t_list *head;
    head = ft_lstnew("hhdo");
	printf("%s", head->content);
}*/
