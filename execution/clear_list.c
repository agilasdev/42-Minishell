/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 00:48:22 by ymourchi          #+#    #+#             */
/*   Updated: 2022/08/26 00:48:25 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_list(char **list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list[i])
		{
			free(list[i]);
			i++;
		}
		free(list);
	}
}

void	del_cmd(void *content)
{
	t_cmd	*cmd;

	if (content)
	{
		cmd = (t_cmd *) content;
		clear_list(cmd->args);
		free(content);
	}
}

void	del_env(void *content)
{
	t_env_content	*env_elem;

	if (content)
	{
		env_elem = (t_env_content *) content;
		if (env_elem->value)
			free(env_elem->value);
		if (env_elem->var)
			free(env_elem->var);
		free(content);
	}
}

void	del_token(void	*content)
{
	t_token	*token;

	if (content)
	{
		token = (t_token *) content;
		if (token->value)
			free(token->value);
		free(token);
	}
}

void	clear_all(t_list **clist, t_list **elist, char **envp)
{
	clear_list(envp);
	ft_lstclear(clist, del_cmd);
	ft_lstclear(elist, del_env);
}
