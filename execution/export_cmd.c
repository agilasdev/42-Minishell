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

int	is_var_valid(int lc, char *str)
{
	if (str[0] && (ft_isalpha(str[0]) || str[0] == '_'))
	{
		if (ft_isalnum(str[lc]) || str[lc] == '_')
			return (1);
	}
	print_error(str, "not a valid identifier\n");
	return (0);
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
		if (!tmp->value && (str[last + 1] == '=' || str[last + 1] == '+'))
			tmp->value = ft_strdup(elem->value);
		else
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

int	export_cmd(char **args, t_list **elist)
{
	int		i;
	int		last;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (!args[i])
		print_env(elist, 1);
	while (args[i])
	{
		last = last_char(args[i], '=');
		if (args[i][last] == '+' && args[i][last + 1] == '=')
			last--;
		if (!is_var_valid(last, args[i]))
			return (1);
		else
			add_var(last, args[i], elist);
		i++;
	}
	return (0);
}
