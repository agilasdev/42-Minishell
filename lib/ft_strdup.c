/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:19:18 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/11 18:22:39 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen(s1);
	c = malloc(l + 1);
	if (c)
	{
		if (s1)
		{
			while (s1[i])
			{
				c[i] = s1[i];
				i++;
			}
		}
		c[i] = '\0';
		return (c);
	}
	return (NULL);
}
