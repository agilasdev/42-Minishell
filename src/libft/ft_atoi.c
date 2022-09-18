/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:23:21 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/18 09:11:55 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	n;
	int			s;

	n = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		n = (n * 10) + (*str - '0');
		str++;
	}
	n *= s;
	if (n > 9223372036854775807 || n < (-922337203685477588 - 1))
		return (-1);
	return ((unsigned char) n);
}
