/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:08:12 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 17:57:19 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			f(i, s + i);
			i++;
		}
	}
}
/*
#include <stdio.h>

void ftcrypt(unsigned int i, char* char_address)
{
	*(char_address) += i * i + 1;
}
void ftdecrypt(unsigned int i, char* char_address)
{
	*(char_address) -= i * i + 1;
}
int main(void)
{
	char *s = ft_strdup("how are you");
	printf("The string : %s\n", s);
	ft_striteri(s, ftcrypt);
	printf("crypted : $%s$\n", s);
	ft_striteri(s, ftdecrypt);
	printf("decrypted : $%s$\n", s);
	free(s);
	return (0);
}*/
