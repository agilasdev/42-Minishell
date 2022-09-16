/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:01:16 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/15 17:01:18 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	chcmd(t_list **clist, t_list **elist, t_cmd *cmd, char **envp)
{
	signal(2, child_sig);
	close_pipes(*clist, cmd);
	if (cmd->args)
	{
		if (cmd->infd)
			dup2(cmd->infd, 0);
		if (cmd->outfd != 1)
			dup2(cmd->outfd, 1);
		if (!ft_strcmp(cmd->args[0], "exit"))
			g_estat = exit_cmd(cmd->args + 1, clist, elist);
		else if (isbuiltin(cmd->args, elist, 1) < 0)
			execute_cmd(cmd, elist, envp);
	}
	exit(g_estat);
}

void	close_pipes(t_list *clist, t_cmd *cmd)
{
	t_cmd	*ccmd;

	while (clist)
	{
		ccmd = (t_cmd *) clist->content;
		if (ccmd != cmd)
		{
			if (ccmd->infd)
				close(ccmd->infd);
			if (ccmd->outfd != 1)
				close(ccmd->outfd);
		}
		clist = clist->next;
	}
}

int	check_path(char **paths, t_cmd *cmd)
{
	char			*cmd_path;
	char			*tmp;
	int				i;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin("/", cmd->args[0]);
		cmd_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (!access(cmd_path, F_OK))
		{
			free(cmd->args[0]);
			cmd->args[0] = cmd_path;
			clear_list(paths);
			return (0);
		}
		free(cmd_path);
	}
	print_error(cmd->args[0], "command not found\n");
	clear_list(paths);
	exit (127);
}

char	*concat_envl(char *var, char *value)
{
	int		lvar;
	int		lvalue;
	char	*envl;

	lvar = ft_strlen(var);
	if (!value)
		return (ft_strdup(var));
	else
		lvalue = ft_strlen(value);
	envl = (char *) malloc(lvar + lvalue + 2);
	ft_memmove(envl, var, lvar);
	envl[lvar] = '=';
	ft_memmove(envl + (lvar + 1), value, lvalue);
	envl[lvar + lvalue + 1] = 0;
	return (envl);
}

void	to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
