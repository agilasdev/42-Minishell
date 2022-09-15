/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:41:35 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 17:41:36 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isflag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	echo_cmd(char **args, int fd)
{
	int	i;
	int	stat;

	i = 0;
	stat = 1;
	while (args[i])
	{
		if (!isflag(args[i]))
			break ;
		i++;
	}
	if (i)
		stat = 0;
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (stat)
		write(fd, "\n", 1);
	return (0);
}
