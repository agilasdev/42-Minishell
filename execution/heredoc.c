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

void	write_in_heredoc(char *delim, int *infd, int stat)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	line = NULL;
	line = readline("> ");
	while (1)
	{
		if (!line || !ft_strcmp(delim, line))
			break ;
		add_history(line);
		if (stat)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
		line = readline("> ");
	}
	if (stat)
		*infd = fd[0];
	else
		close(fd[0]);
	close(fd[1]);
	free(line);
}

void	open_heredoc(t_list *clist)
{
	t_list	*infile;
	t_token	*token;
	t_cmd	*cmd;

	while (clist)
	{
		cmd = (t_cmd *) clist->content;
		infile = cmd->inlist;
		while (infile)
		{
			token = (t_token *) infile->content;
			if (token->e_type == TOKEN_HRDOC)
			{
				if (token == ft_lstlast(cmd->inlist)->content)
					write_in_heredoc(token->value, &cmd->infd, 1);
				else
					write_in_heredoc(token->value, NULL, 0);
			}
			infile = infile->next;
		}
		clist = clist->next;
	}
}
