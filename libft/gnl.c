/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:33:51 by zihihi            #+#    #+#             */
/*   Updated: 2022/01/05 11:39:48 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

// unsigned int	ft_strlen(char *str);
int				nl_in(char **str);
int				reading(int	*ard, int fd, char **abuffer);

char	*gnl(int fd)
{
	static char	*stock;
	char		*buffer;
	int			rd;
	int			nl_idx;

	if (fd < 0)
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	*buffer = '\0';
	nl_idx = nl_in(&stock);
	if (nl_idx >= 0)
		return (deal_with_nl(&stock, nl_idx, &buffer));
	rd = 1;
	while (reading(&rd, fd, &buffer) > 0)
	{
		buffer[rd] = '\0';
		stock = strjoin(&stock, &buffer);
		nl_idx = nl_in(&stock);
		if (nl_idx >= 0)
			return (deal_with_nl(&stock, nl_idx, &buffer));
	}
	return (treat(&stock, rd, &buffer));
}

int	nl_in(char **str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			if ((*str)[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

int	reading(int	*ard, int fd, char **abuffer)
{
	*ard = read(fd, *abuffer, BUFFER_SIZE);
	return (*ard);
}
