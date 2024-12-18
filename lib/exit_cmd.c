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
			if (WIFSIGNALED(stat))
			{
				if (WTERMSIG(stat) == 3)
				{
					write(2, "Quit: 3", 7);
					g_estat = 131;
				}
				else
					g_estat = 130;
				write(2, "\n", 1);
			}
			if (WIFEXITED(stat))
				g_estat = WEXITSTATUS(stat);
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
		stat = g_estat;
	else
		stat = ft_atoi(args[i]);
	if (args && args[i] && args[i + 1] && stat >= 0)
	{
		print_error("exit", "too many arguments\n");
		return (1);
	}
	if (stat < 0)
	{
		print_error(args[i], "numeric argument required\n");
		stat = 255;
	}
	clear_all(clist, elist, NULL);
	exit(stat);
	return (0);
}
