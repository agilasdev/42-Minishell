/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:58:26 by ymourchi          #+#    #+#             */
/*   Updated: 2022/08/26 21:58:28 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_envp(t_list *elist)
{
	int				i;
	char			**envp;
	char			*tmp1;
	char			*tmp2;
	t_env_content	*env_elem;

	i = ft_lstsize(elist);
	envp = (char **) malloc(sizeof(char *) * (i + 1));
	envp[i] = NULL;
	i = 0;
	while (elist)
	{
		env_elem = (t_env_content *) elist->content;
		tmp1 = ft_strjoin(env_elem->var, "=");
		tmp2 = ft_strjoin(tmp1, env_elem->value);
		free(tmp1);
		envp[i] = tmp2;
		i++;
		elist = elist->next;
	}
	return (envp);
}

t_env_content	*set_content(char *str)
{
	t_env_content	*env_c;
	int				i;

	env_c = malloc(sizeof(t_env_content));
	if (!env_c)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				env_c->var = ft_substr(str, 0, i - 1);
			else
				env_c->var = ft_substr(str, 0, i);
			env_c->value = ft_strdup(str + i + 1);
			return (env_c);
		}
	}
	env_c->var = ft_strdup(str);
	env_c->value = NULL;
	return (env_c);
}

void	fill_env_list(char *envp[], t_list **elist)
{
	t_list			*node;
	t_env_content	*c;
	int				i;

	*elist = 0;
	i = -1;
	while (envp[++i])
	{
		c = set_content(envp[i]);
		node = ft_lstnew((void *) c);
		ft_lstadd_back(elist, node);
	}
	if (!get_content("OLDPWD", elist))
		ft_lstadd_back(elist, ft_lstnew(set_content("OLDPWD")));
	c = get_content("_", elist);
	free(c->value);
	c->value = ft_strdup("/usr/bin/env");
}

t_env_content	*get_content(char *var, t_list **elist)
{
	t_list			*tmp;
	t_env_content	*content;

	tmp = *elist;
	while (tmp)
	{
		content = (t_env_content *) tmp->content;
		if (!ft_strcmp(var, content->var))
			return (content);
		tmp = tmp->next;
	}
	return (NULL);
}
