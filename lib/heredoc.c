/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 23:34:19 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/10 23:34:21 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_herdoc(char *delim, int *fd, int stat, t_list **elist)
{
	char	*line;

	signal(2, heredoc_sig);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(delim, line))
			break ;
		add_history(line);
		if (stat)
		{
			expand_heredoc(&line, elist);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

int	write_in_heredoc(char *delim, int *infd, int stat, t_list **elist)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (0);
	if (!pid)
		child_herdoc(delim, fd, stat, elist);
	waitpid(pid, &g_estat, 0);
	if (WIFEXITED(g_estat))
		g_estat = WEXITSTATUS(g_estat);
	if (stat && !g_estat)
		*infd = fd[0];
	else
		close(fd[0]);
	close(fd[1]);
	return (g_estat);
}

int	open_heredoc(t_list *clist, t_list **elist)
{
	t_list	*infile;
	t_token	*token;
	t_cmd	*cmd;
	int		stat;

	while (clist)
	{
		cmd = (t_cmd *) clist->content;
		infile = cmd->inlist;
		while (infile)
		{
			token = (t_token *) infile->content;
			stat = 0;
			if (!infile->next)
				stat = 1;
			if (token->e_type == TOKEN_HRDOC)
			{
				if (write_in_heredoc(token->value, &cmd->infd, stat, elist))
					return (0);
			}
			infile = infile->next;
		}
		clist = clist->next;
	}
	return (1);
}
