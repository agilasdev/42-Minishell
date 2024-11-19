/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:06:26 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/14 13:16:35 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	size_t	isset(char c, char const *set, size_t len)
{
	size_t	l;

	l = len;
	while (l-- > 0)
	{
		if (c == set[l])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*s;
	char		*r;
	size_t		l2;
	size_t		i;
	size_t		t;

	if (!s1)
		return (0);
	t = ft_strlen(s1);
	l2 = ft_strlen(set);
	s = s1 + t - 1 ;
	i = 0;
	while (t > 0 && isset(*s, set, l2))
	{
		s--;
		t--;
	}
	while (t > 0 && isset(*s1, set, l2))
	{
		t--;
		s1++;
		i++;
	}
	r = ft_substr(s1, 0, t);
	return (r);
}
