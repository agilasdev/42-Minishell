#include "../include/minishell.h"

void	init_cmd(t_cmd **addr_pcmd)
{
	t_cmd	*cmd = *addr_pcmd;

	cmd->inlist = 0;
	cmd->outlist = 0;
	cmd->args = 0;
}

t_list	*create_cmd_list(t_list **tokens_list)
{
	t_list	*cmd_list = 0;
	t_list	*cmd_args = 0;
	t_list	*tmp;

	tmp = *tokens_list;
	
	t_cmd	*cmd = ft_calloc(1, sizeof(t_cmd));
	
	while (tmp)
	{
		t_token *curr_token = tmp->content;

		if (is_redir(curr_token->e_type))
		{
			// add file;
			t_token *file = malloc(sizeof(t_file));
			
			t_token *nxt_token = tmp->next->content;
			
			file->value = ft_strdup(nxt_token->value);
			file->e_type = curr_token->e_type;
			tmp = tmp->next->next;
			if (file->e_type == TOKEN_HRDOC || file->e_type == TOKEN_IN)
				ft_lstadd_back(&cmd->inlist, ft_lstnew(file));
			else
				ft_lstadd_back(&cmd->outlist, ft_lstnew(file));
		}
		else if (is_pipe(curr_token->e_type))
		{
			//set_cmd
			cmd->args = list_to_array(&cmd_args);
			ft_lstclear(&cmd_args, free);
			cmd_args = 0;
			ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
			cmd = ft_calloc(1, sizeof(t_cmd));
			tmp = tmp->next;
		}
		else
		{
			//	add_arg
			ft_lstadd_back(&cmd_args, ft_lstnew(ft_strdup(curr_token->value)));
			tmp = tmp->next;
		}
	}
	cmd->args = list_to_array(&cmd_args);
	ft_lstclear(&cmd_args, free);
	cmd_args = 0;
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));

	return (cmd_list);
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
		result[i] = ft_strdup(tmp->content);	// content of list must be char *
		i++;
		tmp = tmp->next;
	}
	result[i] = 0;
	return (result);
}