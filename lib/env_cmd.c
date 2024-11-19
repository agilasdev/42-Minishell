/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:46:44 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 16:46:46 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_list **elist, int fd)
{
	t_list			*envl;
	t_env_content	*content;

	envl = *elist;
	while (envl)
	{
		content = (t_env_content *) envl->content;
		if (ft_strcmp(content->var, "_"))
		{
			write(fd, "declare -x ", 11);
			write(fd, content->var, ft_strlen(content->var));
			if (content->value)
			{
				write(fd, "=", 1);
				write(fd, "\"", 1);
				write(fd, content->value, ft_strlen(content->value));
				write(fd, "\"", 1);
			}
			write(fd, "\n", 1);
		}
		envl = envl->next;
	}
}

void	print_env(t_list **elist, int fd)
{
	t_list			*envl;
	t_env_content	*content;

	envl = *elist;
	while (envl)
	{
		content = (t_env_content *) envl->content;
		if (content->value)
		{
			write(fd, content->var, ft_strlen(content->var));
			write(fd, "=", 1);
			write(fd, content->value, ft_strlen(content->value));
			write(fd, "\n", 1);
		}
		envl = envl->next;
	}
}

int	env_cmd(char **args, t_list **elist, int fd)
{
	int	i;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (args[i])
	{
		print_error(args[i], "No such file or directory\n");
		return (127);
	}
	else
		print_env(elist, fd);
	return (0);
}
