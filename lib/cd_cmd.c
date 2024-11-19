/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:27:17 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 17:27:18 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*destpath(char **args, t_list **elist)
{
	int				i;
	char			*path;
	t_env_content	*home;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	home = get_content("HOME", elist);
	if (!args[i] || *args[i] == '~')
	{
		if (!home)
		{
			print_error("cd", "HOME not set\n");
			return (NULL);
		}
		if (!args[i])
			path = ft_strdup(home->value);
		else
			path = ft_strjoin(home->value, args[i] + 1);
	}
	else
		path = ft_strdup(args[i]);
	return (path);
}

void	update_pwd(char *curdir, t_list **elist)
{
	t_env_content	*pwd;
	t_env_content	*oldpwd;

	pwd = get_content("PWD", elist);
	oldpwd = get_content("OLDPWD", elist);
	if (pwd && oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
	}
	if (!oldpwd)
		ft_lstadd_back(elist, ft_lstnew(set_content("OLDPWD")));
	if (!pwd)
	{
		pwd = set_content("PWD");
		ft_lstadd_back(elist, ft_lstnew(pwd));
	}
	pwd->value = curdir;
}

int	cd_cmd(char **args, t_list **elist)
{
	char			*path;
	char			*curdir;

	path = destpath(args, elist);
	if (!path)
		return (1);
	if (chdir(path))
	{
		print_error(path, NULL);
		free(path);
		return (1);
	}
	free (path);
	curdir = getcwd(NULL, 0);
	if (!curdir)
		print_error("getcwd: cannot access parent directories", NULL);
	else
		update_pwd(curdir, elist);
	return (0);
}
