/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:55:41 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/11 18:08:24 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(count * size);
	// void *p = malloc(size);
    // printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);
	printf("Allocated = %p [%li]  \n", s, size*count);
	if (s)
	{
		ft_bzero(s, count * size);
		return (s);
	}
	return (NULL);
}
