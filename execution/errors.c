/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:52:45 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/03 23:52:47 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *cmd, char *err_msg)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
	else
		perror("");
}

void	parent_sig(int sig)
{
	if (sig == 2)
	{
		g_estat = 1;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_sig(int sig)
{
	if (sig == 2)
		exit(130);
}

void	heredoc_sig(int sig)
{
	if (sig == 2)
		exit(1);
}
