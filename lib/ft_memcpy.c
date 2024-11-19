/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:18:30 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 17:08:33 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	s = src;
	d = dest;
	if (!src && !d)
		return (NULL);
	while (n-- > 0)
	{
		*d++ = *s++;
	}
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
	char s[] = "hello, world!";
	ft_memmove(s + 2, s, 4); // overlap handeled!
	printf("%s\n", s);
}*/
