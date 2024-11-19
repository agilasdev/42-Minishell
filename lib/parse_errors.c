/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:46:05 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/21 08:26:52 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_error_msg(char *s, int exit_num, int *err_nb)
{
	write(2, "MiniShell: syntax error near unexpected token `", 47);
	write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
	g_estat = exit_num;
	*err_nb = 1;
	return (1);
}

int	check_errors(t_list **tokens_list)
{
	t_list	*tmp;
	t_token	*token;
	int		err_nb;

	tmp = *tokens_list;
	token = tmp->content;
	err_nb = 0;
	if (!tmp->next)
	{
		if (!(is_pipe(token->e_type) || is_redir(token->e_type)))
			return (0);
	}
	if (token->e_type == TOKEN_PIPE)
		ft_error_msg("|", 258, &err_nb);
	while (!err_nb && tmp)
	{
		conditions(&tmp, &err_nb);
		tmp = tmp->next;
	}
	if (err_nb)
		return (1);
	return (0);
}

void	conditions(t_list **atmp, int *err_nb)
{
	t_token	*token;
	t_token	*next_token;
	int		type_next;

	token = (*atmp)->content;
	next_token = 0;
	if (token->e_type != TOKEN_STR && (*atmp)->next == 0)
		ft_error_msg("newline", 258, err_nb);
	if ((*atmp)->next == 0)
		type_next = -1;
	else
	{
		next_token = (*atmp)->next->content;
		type_next = next_token->e_type;
	}
	if (next_token)
		errors_cases(token->e_type, type_next, next_token->value, err_nb);
}

void	errors_cases(int type_curr, int type_next, char *value, int *err_nb)
{
	(void)value;
	if (is_redir(type_curr) && is_redir(type_next))
		ft_error_msg(value, 258, err_nb);
	else if (is_pipe(type_curr) && is_pipe(type_next))
		ft_error_msg("|", 258, err_nb);
	else if (is_redir(type_curr) && is_pipe(type_next))
		ft_error_msg("|", 258, err_nb);
	else if (is_redir(type_curr) && not_str(type_next))
		ft_error_msg("|", 258, err_nb);
}
