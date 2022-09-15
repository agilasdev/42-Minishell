/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:47:35 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 16:47:37 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	statexit(int pid, int len)
{
	int	stat;

	while (len--)
	{
		if (waitpid(-1, &stat, 0) == pid)
		{
			if (WIFEXITED(stat))
				g_estat = WEXITSTATUS(stat);
			else
				g_estat = 0;
		}
	}
}

int	exit_cmd(char **args, t_list **clist, t_list **elist)
{
	int	i;
	int	stat;

	i = 0;
	if (args && args[i] && !ft_strcmp(args[i], "--"))
		i++;
	printf("exit\n");
	if (!args || !args[i])
		stat = 0;
	else
		stat = ft_atoi(args[i]);
	if (stat < 0)
	{
		print_error(args[i], "numeric argument required\n");
		stat = 255;
	}
	if (args && args[i] && args[i + 1] && stat >= 0)
	{
		print_error("exit", "too many arguments\n");
		return (1);
	}
	clear_all(clist, elist, NULL);
	exit(stat);
	return (0);
}
