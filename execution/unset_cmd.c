/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:25:48 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 17:25:50 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	rm_env_elem(void *c, t_list **elist)
{
	t_list	*envl;
	t_list	*tmp;

	envl = *elist;
	if (envl->content == c)
	{
		*elist = envl->next;
		free(envl);
		return (0);
	}
	while (envl->next)
	{
		if (envl->next->content == c)
		{
			tmp = envl->next->next;
			ft_lstdelone(envl->next, del_env);
			if (!tmp)
				envl->next = NULL;
			else
				envl->next = tmp;
			break ;
		}
		envl = envl->next;
	}
	return (0);
}

int	unset_cmd(char **args, t_list **elist)
{
	int				i;
	t_env_content	*envl;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_"))
		{
			if (is_var_valid(ft_strlen(args[i]) - 1, args[i]))
			{
				envl = get_content(args[i], elist);
				if (envl)
					rm_env_elem((void *)envl, elist);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}
