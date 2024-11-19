/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:18:32 by ymourchi          #+#    #+#             */
/*   Updated: 2022/08/31 19:18:40 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(char *line, t_list **elist)
{
	t_list	*tknlist;
	t_list	*clist;

	add_history(line);
	tknlist = expand_tokens(line, elist);
	if (tknlist && !check_errors(&tknlist))
	{
		clist = create_cmd_list(&tknlist);
		ft_lstclear(&tknlist, del_token);
		execution(&clist, elist);
	}
	if (tknlist)
		ft_lstclear(&tknlist, del_token);
}
