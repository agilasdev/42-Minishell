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

int	pwd_cmd(t_list **elist)
{
	t_env_content	*elem;

	elem = get_content("PWD", elist);
	printf("%s\n", elem->value);
	return (0);
}
