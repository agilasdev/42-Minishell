/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:44:13 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 17:02:38 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len--)
	{
		*s++ = (unsigned char) c;
	}
	return (b);
}
/*#include <stdio.h>
#include <string.h>
int main(void)
{
	void  *s = malloc(sizeof(unsigned char) * 5);
	s = ft_memset(s, 126, 4);
	printf("%s\n", (char *) s);
}*/
