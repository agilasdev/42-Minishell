/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:18:15 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 20:37:22 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*tmp;

	newlist = NULL;
	while (lst && f)
	{
		tmp = ft_lstnew(f(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, tmp);
		lst = lst -> next;
	}
	return (newlist);
}
/*#include <stdio.h>
#include <stdlib.h>
void	*func(void * s)
{
	char *t;
	t = s;
	while (*t)
	{
		if (*t >= '0' && *t <= '9')
			*t += 1;
		t++;
	}
	return (s);
}
int main(void)
{
	t_list *lst;
	lst = ft_lstnew(ft_strdup("1st node"));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("2nd node")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("3rd node")));
	t_list *new_lst = ft_lstmap(lst, func, free);

	ft_lstadd_front(&new_lst, ft_lstnew(ft_strdup("1st node")));
	ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup("5th node")));
	t_list *tmp = new_lst;
	while (tmp)
	{
		printf("%s -> ", tmp -> content);
		tmp = tmp -> next;
	}
	printf("%s\n", (char *) tmp);
	ft_lstclear(&new_lst, free);
	printf("%s\n", new_lst->content);
}*/
