/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:50:14 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 22:07:13 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_substitute(t_lexer *lexer, char **value, t_list **env_list,
		int pretype)
{
	if (lexer->c == '\'')
		ft_handle_sq(lexer, value);
	else if (lexer->c == '$')
		ft_handle_dollar(lexer, value, env_list, pretype);
	else if (lexer->c == '"')
		ft_handle_dq(lexer, value, env_list, pretype);
}

void	ft_treat_str(t_token *token, t_list **tokens_list, t_list **env_list,
		int pretype)
{
	char	*value;
	t_lexer	*lexer;

	value = ft_calloc(1, sizeof(char));
	lexer = init_lexer(token->value);
	while (lexer->c)
	{
		if (lexer->c == '$' || lexer->c == '"' || lexer->c == '\'')
			ft_substitute(lexer, &value, env_list, pretype);
		else
		{
			add_up_char(lexer, &value);
			lexer_advance(lexer);
		}
	}
	add_token(&token, &value, tokens_list);
	free(lexer);
}

int	to_be_treated(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' || str[i] == '"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

void	ft_handle_sq(t_lexer *lexer, char **value)
{
	char	sq;

	sq = lexer->c;
	lexer_advance(lexer);
	while (lexer->c != sq)
	{
		add_up_char(lexer, value);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
}

void	add_token(t_token **atoken, char **avalue, t_list **tokens_list)
{
	t_token	*token;
	char	*value;

	token = *atoken;
	value = *avalue;
	free(token->value);
	if (value && value[0] == '\0')
	{
		free(value);
		token->value = 0;
		if (*atoken && g_estat != -2)
		{
			free(*atoken);
			*atoken = 0;
		}
	}
	else
	{
		token->value = value;
		ft_lstadd_back(tokens_list, ft_lstnew(token));
	}
}
