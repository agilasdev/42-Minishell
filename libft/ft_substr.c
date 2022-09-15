/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:41:08 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/29 14:42:43 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;
	size_t	l;

	i = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
	{
		t = ft_calloc(1, 1);
		return (t);
	}
	if (len < l)
		l = len;
	t = malloc(sizeof(char) * (l + 1));
	if (t == NULL)
		return (NULL);
	while (i < l && s[start + i])
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
