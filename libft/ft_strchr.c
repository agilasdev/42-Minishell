/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                       :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:19:08 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 17:16:04 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*d;
	int		i;

	d = (char *) s;
	i = -1;
	while (d[++i])
	{
		if (d[i] == (char) c)
			return (d + i);
	}
	if (d[i] == (char) c)
		return (d + i);
	return (NULL);
}
