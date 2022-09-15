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

void	print_env(t_list **elist, char stat)
{
	t_list			*envl;
	t_env_content	*content;

	envl = *elist;
	while (envl)
	{
		content = (t_env_content *) envl->content;
		if (stat)
		{
			if (ft_strcmp(content->var, "_"))
			{
				if (content->value)
					printf("declare -x %s=\"%s\"\n", content->var, content->value);
				else
					printf("declare -x %s\n", content->var);
			}
		}
		else
		{
			if (content->value)
				printf("%s=%s\n", content->var, content->value);
		}
		envl = envl->next;
	}
}

int	env_cmd(char **args, t_list **elist)
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
		print_env(elist, 0);
	return (0);
}
