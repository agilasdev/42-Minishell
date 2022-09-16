#include "../include/minishell.h"

// void	ft_error_msg(char *s, int exit_num)
// {
// 	write(2, "MiniShell: syntax error near unexpected token `", 47);
// 	write(2, s, ft_strlen(s));
// 	write(2, "'\n", 2);
// 	g_estat = exit_num;
// }

// void	check_errors(t_list **tokens_list)
// {
// 	t_list	*tmp;

// 	t_token	*token;
// 	t_token	*next_token;
	
// 	int		type_curr;
// 	int		type_next;

// 	tmp = *tokens_list;
// 	token = tmp->content;
// 	if (token->e_type == TOKEN_PIPE)
// 		ft_error_msg("|", 258);
// 	while (!g_estat && tmp)
// 	{
// 		// printf("piw\n");
// 		token = tmp->content;
// 		if (token->e_type == TOKEN_PIPE && tmp->next == 0)
// 			ft_error_msg("|", 258);
// 		type_curr = token->e_type;
// 		if (!tmp->next)
// 			type_next = -1;
// 		else
// 		{
// 			next_token = tmp->next->content;
// 			type_next = next_token->e_type;
// 		}
// 		if (is_redir(type_curr) && is_redir(type_next))
// 			ft_error_msg(next_token->value, 258);
// 		else if (is_pipe(type_curr) && is_pipe(type_next))
// 			ft_error_msg(next_token->value, 258);
// 		else if (is_redir(type_curr) && is_pipe(type_next))
// 			ft_error_msg(next_token->value, 258);
// 		else if (is_redir(type_curr) && not_str(type_next))
// 			ft_error_msg(next_token->value, 258);
// 		tmp = tmp->next;
// 	}
// }