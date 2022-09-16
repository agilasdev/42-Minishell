/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:24:35 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/09 18:24:38 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_pipes(t_list *clist)
{
	t_cmd	*c_cmd;
	t_cmd	*n_cmd;
	int		fd[2];

	while (clist->next)
	{
		c_cmd = (t_cmd *) clist->content;
		n_cmd = (t_cmd *) clist->next->content;
		if (pipe(fd) < 0)
		{
			print_error("pipe", NULL);
			return (0);
		}
		if (!c_cmd->outlist)
			c_cmd->outfd = fd[1];
		else
			close(fd[1]);
		if (!n_cmd->inlist)
			n_cmd->infd = fd[0];
		else
			close(fd[0]);
		clist = clist->next;
	}
	return (1);
}

int	open_infile(t_cmd *cmd)
{
	t_token	*token;
	t_list	*infile;
	int		fd;

	infile = cmd->inlist;
	while (infile)
	{
		token = (t_token *) infile->content;
		if (token->e_type == TOKEN_IN)
		{
			fd = open(token->value, O_RDONLY);
			if (fd < 0)
			{
				print_error(token->value, NULL);
				return (0);
			}
			if (infile == cmd->inlist)
				cmd->infd = fd;
			else
				close(fd);
		}
		infile = infile->next;
	}
	return (1);
}

int	open_outfile(t_cmd *cmd)
{
	t_token	*token;
	t_list	*outfile;
	int		fd;

	outfile = cmd->outlist;
	while (outfile)
	{
		token = (t_token *) outfile->content;
		if (token->e_type == TOKEN_OUT)
			fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (token->e_type == TOKEN_APP)
			fd = open(token->value, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd < 0)
		{
			print_error(token->value, NULL);
			return (0);
		}
		if (!outfile->next)
			cmd->outfd = fd;
		else
			close(fd);
		outfile = outfile->next;
	}
	return (1);
}

int	open_files(t_list **clist, t_list **env_list)
{
	t_list	*lst;
	t_cmd	*cmd;

	lst = *clist;
	if (!open_heredoc(lst))
		return (0);
	while (lst)
	{
		cmd = (t_cmd *) lst->content;
		if (*clist == lst && !cmd->inlist)
			cmd->infd = 0;
		if (!lst->next && !cmd->outlist)
			cmd->outfd = 1;
		if (!open_infile(cmd) || !open_outfile(cmd))
		{
			ft_lstclear(env_list, del_env);
			ft_lstclear(clist, del_cmd);
			g_estat = 1;
			return (0);
		}
		lst = lst->next;
	}
	if (!open_pipes(*clist))
		return (0);
	return (1);
}
