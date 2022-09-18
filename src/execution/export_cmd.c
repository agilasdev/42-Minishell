/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:42:41 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/01 16:42:49 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	last_char(char *str, int last)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i + 1] == last)
			return (i);
		i++;
	}
	return (i - 1);
}

int	is_var_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		print_error(str, "not a valid identifier\n");
		return (0);
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			print_error(str, "not a valid identifier\n");
			return (0);
		}
	}
	return (1);
}

void	add_var(int last, char *str, t_list **elist)
{
	t_env_content	*elem;
	t_env_content	*tmp;
	char			*val;

	elem = set_content(str);
	tmp = get_content(elem->var, elist);
	if (!tmp)
		ft_lstadd_back(elist, ft_lstnew((void *) elem));
	else
	{
		if (!tmp->value && elem->value)
			tmp->value = ft_strdup(elem->value);
		else if (tmp->value && elem->value)
		{
			val = tmp->value;
			if (str[last + 1] == '=')
				tmp->value = ft_strdup(elem->value);
			if (str[last + 1] == '+')
				tmp->value = ft_strjoin(tmp->value, elem->value);
			free(val);
		}
		del_env(elem);
	}
}

int	export_cmd(char **args, t_list **elist, int fd)
{
	int		i;
	int		last;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (!args[i])
		print_export(elist, fd);
	while (args[i])
	{
		last = last_char(args[i], '=');
		if (args[i][last] == '+' && args[i][last + 1] == '=')
			last--;
		if (!is_var_valid(args[i]))
			return (1);
		else
			add_var(last, args[i], elist);
		i++;
	}
	return (0);
}
