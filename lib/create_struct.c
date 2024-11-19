/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:39:23 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/14 07:39:31 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_vars1(t_list **clist, t_list **arglist, t_cmd **cmd)
{
	*clist = 0;
	*arglist = 0;
	*cmd = ft_calloc(1, sizeof(t_cmd));
}

t_list	*create_cmd_list(t_list **tokens_list)
{
	t_list	*cmd_list;
	t_list	*arglist;
	t_cmd	*cmd;
	t_list	*tmp;
	t_token	*curr_token;

	tmp = *tokens_list;
	init_vars1(&cmd_list, &arglist, &cmd);
	while (tmp)
	{
		curr_token = tmp->content;
		if (is_redir(curr_token->e_type))
			add_file(&cmd, &tmp);
		else if (is_pipe(curr_token->e_type))
		{
			add_cmd(&cmd, &arglist, &cmd_list);
			cmd = ft_calloc(1, sizeof(t_cmd));
		}
		else
			ft_lstadd_back(&arglist, ft_lstnew(ft_strdup(curr_token->value)));
		tmp = tmp->next;
	}
	add_cmd(&cmd, &arglist, &cmd_list);
	return (cmd_list);
}

void	add_cmd(t_cmd **acmd, t_list **arglist, t_list **cmd_list)
{
	(*acmd)->args = list_to_array(arglist);
	(*acmd)->infd = 0;
	(*acmd)->outfd = 1;
	ft_lstclear(arglist, free);
	*arglist = 0;
	ft_lstadd_back(cmd_list, ft_lstnew(*acmd));
}

void	add_file(t_cmd **acmd, t_list **tmp)
{
	t_token	*file;
	t_token	*curr_token;
	t_token	*next_token;
	t_cmd	*cmd;

	cmd = *acmd;
	file = malloc(sizeof(t_token));
	curr_token = (*tmp)->content;
	next_token = (*tmp)->next->content;
	file->value = ft_strdup(next_token->value);
	file->e_type = curr_token->e_type;
	(*tmp) = (*tmp)->next;
	if (file->e_type == TOKEN_HRDOC || file->e_type == TOKEN_IN)
		ft_lstadd_back(&cmd->inlist, ft_lstnew(file));
	else
		ft_lstadd_back(&cmd->outlist, ft_lstnew(file));
}

char	**list_to_array(t_list **lst)
{
	char	**result;
	t_list	*tmp;
	int		size;
	int		i;

	tmp = *lst;
	size = ft_lstsize(*lst);
	if (size == 0)
		return (0);
	result = malloc((size + 1) * sizeof(char *));
	if (result == 0)
		return (0);
	tmp = *lst;
	i = 0;
	while (tmp)
	{
		result[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	result[i] = 0;
	return (result);
}
