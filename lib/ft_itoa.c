/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:12:33 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/18 04:05:31 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*alloc_strnb(int len);
static void	fill_str(char *str, int n, int len);
static void	dofill(char *str, int n, int len);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nb;

	nb = n;
	if (n < 0)
		nb = n * (-1);
	len = 0;
	if (n == -2147483648)
		len = 10;
	else if (nb < 10 && nb)
		len = 1;
	else
	{
		while (nb)
		{
			len++;
			nb = (nb / 10);
		}
	}
	str = alloc_strnb(len);
	if (str)
		dofill(str, n, len);
	return (str);
}

static	char	*alloc_strnb(int len)
{
	return (malloc(sizeof(char) * (len + 2)));
}

static void	dofill(char *str, int n, int len)
{
	if (n == -2147483648)
	{
		fill_str(str, -2147483647, len);
		*(str + len) = '8';
	}
	else
		fill_str(str, n, len);
}

static void	fill_str(char *str, int n, int len)
{
	char	*tmp;

	tmp = str + len + 1;
	*tmp = 0;
	tmp--;
	if (n > 0)
	{
		*tmp = 0;
		tmp--;
	}
	else if (!n)
		*str = '0';
	else
	{
		*str = '-';
		n *= -1;
	}
	while (len--)
	{
		*tmp = (n % 10) + '0';
		n = (n / 10);
		tmp--;
	}
}
