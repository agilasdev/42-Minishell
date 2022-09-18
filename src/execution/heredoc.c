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

void	wherdoc(char *delim, int *fd, int stat)
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
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

int	write_in_heredoc(char *delim, int *infd, int stat)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (0);
	if (!pid)
		wherdoc(delim, fd, stat);
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

int	open_heredoc(t_list *clist)
{
	t_list	*infile;
	t_token	*token;
	t_cmd	*cmd;

	while (clist)
	{
		cmd = (t_cmd *) clist->content;
		if (cmd)
		{
			cmd->infd = 0;
			cmd->outfd = 1;
			infile = cmd->inlist;
			while (infile)
			{
				token = (t_token *) infile->content;
				if (!tkn_herdoc(cmd, token))
					return (0);
				infile = infile->next;
			}
		}
		clist = clist->next;
	}
	return (1);
}

int	tkn_herdoc(t_cmd *cmd, t_token *token)
{
	if (token->e_type == TOKEN_HRDOC)
	{
		if (token == ft_lstlast(cmd->inlist)->content)
		{
			if (write_in_heredoc(token->value, &cmd->infd, 1))
				return (0);
		}
		else
		{
			if (write_in_heredoc(token->value, NULL, 0))
				return (0);
		}
	}
	return (1);
}
