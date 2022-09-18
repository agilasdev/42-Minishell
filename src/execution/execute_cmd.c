/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:14:37 by ymourchi          #+#    #+#             */
/*   Updated: 2022/08/25 19:14:45 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_list **clist, t_list **elist)
{
	char	**envp;
	t_cmd	*cmd;

	envp = NULL;
	signal (2, SIG_IGN);
	if (open_heredoc(*clist) && open_pipes(*clist))
	{
		envp = create_envp(*elist);
		if (ft_lstsize(*clist) == 1)
		{
			cmd = (*clist)->content;
			if (cmd)
			{
				onecmd(clist, elist, envp);
				if (cmd->infd)
					close(cmd->infd);
				if (cmd->outfd != 1)
					close(cmd->outfd);
			}
		}
		else
			morecmds(clist, elist, envp);
		clear_list(envp);
	}
	ft_lstclear(clist, del_cmd);
}

void	onecmd(t_list **clist, t_list **elist, char **envp)
{
	t_cmd	*cmd;
	int		pid;

	cmd = (t_cmd *)(*clist)->content;
	if (open_infile(cmd) && open_outfile(cmd) && cmd->args)
	{
		to_lower(cmd->args[0]);
		if (!ft_strcmp(cmd->args[0], "exit"))
			g_estat = exit_cmd(cmd->args + 1, clist, elist);
		else
			g_estat = isbuiltin(cmd->args, elist, cmd->outfd);
		if (g_estat < 0)
		{
			pid = fork();
			if (!pid)
			{
				if (cmd->infd)
					dup2(cmd->infd, 0);
				if (cmd->outfd != 1)
					dup2(cmd->outfd, 1);
				execute_cmd(cmd, elist, envp);
			}
			statexit(pid, 1);
		}
	}
}

void	morecmds(t_list **clist, t_list **elist, char **envp)
{
	t_cmd	*cmd;
	t_list	*tmp;
	int		pid;

	tmp = *clist;
	while (tmp)
	{
		cmd = (t_cmd *) tmp->content;
		pid = fork();
		if (pid < 0)
		{
			print_error("fork", NULL);
			break ;
		}
		if (!pid)
			chcmd(clist, elist, cmd, envp);
		if (cmd->infd)
			close(cmd->infd);
		if (cmd->outfd != 1)
			close(cmd->outfd);
		tmp = tmp->next;
	}
	statexit(pid, ft_lstsize(*clist));
}

int	isbuiltin(char **args, t_list **elist, int fd)
{
	int	stat;

	if (!ft_strcmp(args[0], "cd"))
		stat = cd_cmd(args + 1, elist);
	else if (!ft_strcmp(args[0], "export"))
		stat = export_cmd(args + 1, elist, fd);
	else if (!ft_strcmp(args[0], "env"))
		stat = env_cmd(args + 1, elist, fd);
	else if (!ft_strcmp(args[0], "echo"))
		stat = echo_cmd(args + 1, fd);
	else if (!ft_strcmp(args[0], "unset"))
		stat = unset_cmd(args + 1, elist);
	else if (!ft_strcmp(args[0], "pwd"))
		stat = pwd_cmd(elist, fd);
	else
		return (-1);
	return (stat);
}

void	execute_cmd(t_cmd	*cmd, t_list **elist, char **envp)
{
	t_env_content	*elem;

	signal(2, child_sig);
	signal(3, child_sig);
	elem = get_content("PATH", elist);
	if (!ft_strcmp(cmd->args[0], "minishell"))
	{
		free(cmd->args[0]);
		cmd->args[0] = ft_strdup("./minishell");
	}
	if (!ft_strchr(cmd->args[0], '/') && elem)
		check_path(ft_split(elem->value, ':', NULL), cmd);
	if (access(cmd->args[0], F_OK))
	{
		print_error(cmd->args[0], NULL);
		exit(127);
	}
	execve(cmd->args[0], cmd->args, envp);
	print_error(cmd->args[0], NULL);
	exit(errno);
}
