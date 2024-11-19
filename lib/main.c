/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:38:08 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/25 01:32:15 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int g_estat= 0;
int	main(int ac, char **av, char **envp)
{
	t_list	*elist;
	char	*line;

	if (ac > 1)
	{
		printf("Try again with no Args :3\n");
		exit(0);
	}
	// av = NULL;
	// *av = NULL;
	g_estat = 0;
	(void)av;
	fill_env_list(envp, &elist);
	signal(3, SIG_IGN);
	while (1)
	{
		signal(2, parent_sig);
		line = readline("Minishell-0.1$ ");
		if (!line)
			exit_cmd(NULL, NULL, NULL);
		if (line[0])
			minishell(line, &elist);
		free(line);
	}
	ft_lstclear(&elist, del_env);
	return (g_estat);
}
