/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:46:05 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/14 11:46:11 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_error_msg(char *s, int exit_num)
{
	write(2, "MiniShell: syntax error near unexpected token `", 47);
	write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
	g_estat = exit_num;
	return (1);
}

int	check_errors(t_list **tokens_list)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*next_token;
	int		type_next;

	tmp = *tokens_list;
	token = tmp->content;
	next_token = 0;
	if (!tmp->next)
	{
		if (!(is_pipe(token->e_type) || is_redir(token->e_type)))
			return (0);
	}
	if (token->e_type == TOKEN_PIPE)
		return (ft_error_msg("|", 258));
	while (!g_estat && tmp)
	{
		token = tmp->content;
		if (token->e_type == TOKEN_PIPE && tmp->next == 0)
			return (ft_error_msg("|", 258));
		if (tmp->next == 0)
			type_next = -1;
		else
		{
			next_token = tmp->next->content;
			type_next = next_token->e_type;
		}
		if (next_token)
			errors_cases(token->e_type, type_next, next_token->value);
		tmp = tmp->next;
	}
	return (0);
}

void	errors_cases(int type_curr, int type_next, char *value)
{
	if (is_redir(type_curr) && is_redir(type_next))
		ft_error_msg(value, 258);
	else if (is_pipe(type_curr) && is_pipe(type_next))
		ft_error_msg(value, 258);
	else if (is_redir(type_curr) && is_pipe(type_next))
		ft_error_msg(value, 258);
	else if (is_redir(type_curr) && not_str(type_next))
		ft_error_msg(value, 258);
}
