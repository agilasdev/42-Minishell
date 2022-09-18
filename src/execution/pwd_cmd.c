/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:41:43 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 17:41:45 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_cmd(t_list **elist, int fd)
{
	t_env_content	*elem;
	char			*curdir;

	elem = get_content("PWD", elist);
	if (!elem)
	{
		curdir = getcwd(NULL, 0);
		if (!curdir)
			print_error("getcwd: cannot access parent directories", NULL);
		else
		{
			elem = set_content("PWD");
			ft_lstadd_back(elist, ft_lstnew(elem));
			elem->value = curdir;
		}
	}
	if (elem)
	{
		write(fd, elem->value, ft_strlen(elem->value));
		write(fd, "\n", 1);
	}
	return (0);
}
