/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:23:39 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 21:41:24 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*expand_tokens(char *cmd_line, t_list **env_list)
{
	t_lexer	*lexer;
	t_list	*tokens_list;
	t_token	*token;
	int		pretype;

	tokens_list = 0;
	token = 0;
	pretype = -1;
	lexer = init_lexer(cmd_line);
	token = lexer_get_next_token(lexer);
	while (token != 0)
	{
		ft_conditions(token, &tokens_list, env_list, pretype);
		if (g_estat < 0)
		{
			clear_tknlst(token, &tokens_list);
			break ;
		}
		pretype = token->e_type;
		token = lexer_get_next_token(lexer);
	}
	free(lexer);
	if (g_estat < 0)
		clear_tknlst(token, &tokens_list);
	return (tokens_list);
}

void	ft_conditions(t_token *token, t_list **tokens_list, \
		t_list **env_list, int pretype)
{
	if (!ft_strcmp(token->value, "\"\"") || !ft_strcmp(token->value,
			"\'\'"))
	{
		free(token->value);
		token->value = ft_calloc(1, sizeof(char));
		ft_lstadd_back(tokens_list, ft_lstnew(token));
	}
	else if (token->e_type == TOKEN_STR && to_be_treated(token->value))
		ft_treat_str(token, tokens_list, env_list, pretype);
	else
		ft_lstadd_back(tokens_list, ft_lstnew(token));
}

void	clear_tknlst(t_token *token, t_list **tokens_list)
{
	if (token && token->value == 0)
	{
		free(token);
		token = 0;
	}
	g_estat = 1;
	ft_lstclear(tokens_list, del_token);
	tokens_list = 0;
}
