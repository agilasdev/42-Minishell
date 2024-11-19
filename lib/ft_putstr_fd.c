/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pustr_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:18:08 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/28 10:42:49 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write (fd, s, ft_strlen(s));
}
/*
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = open("/Users/zihihi/Desktop/myfile.txt", O_APPEND | O_RDWR);
	ft_putstr_fd("\nfd = ", fd);
	ft_putnbr_fd(fd, 1);
	ft_putnbr_fd(fd, fd);
	return (0);
}*/
