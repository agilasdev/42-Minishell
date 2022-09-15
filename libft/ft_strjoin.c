/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:08:55 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/14 12:58:34 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	r = malloc(sizeof(char) * (l1 + l2 + 1));
	if (r)
	{
		ft_memmove(r, s1, l1);
		ft_memmove(r + l1, s2, l2);
		*(r + l1 + l2) = '\0';
		return (r);
	}
	return (NULL);
}
