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

int	main(int ac, char **av, char **envp)
{
	t_list	*elist;
	t_list	*clist;
	char	*line;
	t_list	*tknlist;

	av = NULL;
	ac = 0;
	elist = NULL;
	g_estat = 0;
	signal(3, SIG_IGN);
	while (1)
	{
		signal(2, parent_sig);
		line = readline("Minishell-0.1$ ");
		if (!line)
			exit_cmd(NULL, NULL, NULL);
		if (line[0])
		{
			add_history(line);
			if (!elist)
				fill_env_list(envp, &elist);
			tknlist = expand_tokens(line, &elist);
			if (!check_errors(&tknlist))
			{
				clist = create_cmd_list(&tknlist);
				execution(&clist, &elist);
			}
			ft_lstclear(&tknlist, del_token);
		}
		free(line);
	}
	ft_lstclear(&elist, del_env);
	return (g_estat);
}
