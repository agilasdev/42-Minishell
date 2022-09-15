/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:02:50 by zihihi            #+#    #+#             */
/*   Updated: 2022/01/06 16:45:53 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*strjoin(char **addr_s1, char **addr_s2)
{
	char	*tmp;
	int		l1;
	int		l2;
	int		i;

	if (*addr_s1 == NULL)
		return (ft_strdup(*addr_s2));
	l1 = ft_strlen(*addr_s1);
	l2 = ft_strlen(*addr_s2);
	tmp = malloc(sizeof(char) * (l1 + l2 + 1));
	if (tmp)
	{
		i = -1;
		while (tmp && (*addr_s1)[++i])
			tmp[i] = (*addr_s1)[i];
		i = -1;
		while (tmp && (*addr_s2)[++i])
			tmp[l1 + i] = (*addr_s2)[i];
		tmp[l1 + l2] = '\0';
	}
	free(*addr_s1);
	return (tmp);
}

char	*deal_with_nl(char **str, int i, char **to_free)
{
	char	*line;
	char	*tmp;
	char	c;

	if (i + 1 == (int) ft_strlen(*str))
	{
		line = ft_strdup(*str);
		free(*str);
		*str = 0;
	}
	else
	{
		c = (*str)[i + 1];
		(*str)[i + 1] = '\0';
		line = ft_strdup(*str);
		(*str)[i + 1] = c;
		tmp = ft_strdup((*str) + i + 1);
		free(*str);
		*str = tmp;
	}
	if (*to_free)
		free(*to_free);
	*to_free = 0;
	return (line);
}

char	*treat(char **astock, int rd, char **to_free)
{
	char	*line;

	if (rd < 0)
	{
		if (*astock)
		{
			free(*astock);
			*astock = 0;
		}
		line = 0;
	}
	else
	{
		line = *astock;
		*astock = 0;
	}
	free(*to_free);
	return (line);
}
