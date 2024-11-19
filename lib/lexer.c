/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:22:18 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 15:02:45 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*out_token(t_lexer *lexer)
{
	char	*str;

	if (lexer->content[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		str = ft_strdup(">>");
		return (lexer_advance_with_token(lexer, create_token(TOKEN_APP,
					&str)));
	}
	str = lexer_get_current_char_as_string(lexer);
	return (lexer_advance_with_token(lexer, create_token(TOKEN_OUT,
				&str)));
}

t_token	*in_token(t_lexer *lexer)
{
	char	*str;

	if (lexer->content[lexer->i + 1] == '<')
	{
		lexer_advance(lexer);
		str = ft_strdup("<<");
		return (lexer_advance_with_token(lexer,
				create_token(TOKEN_HRDOC, &str)));
	}
	str = lexer_get_current_char_as_string(lexer);
	return (lexer_advance_with_token(lexer, create_token(TOKEN_IN,
				&str)));
}

t_token	*pipe_token(t_lexer *lexer)
{
	char	*str;

	str = lexer_get_current_char_as_string(lexer);
	return (lexer_advance_with_token(lexer, create_token(TOKEN_PIPE,
				&str)));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < lexer->len)
	{
		if (is_white_space(lexer->c))
			lexer_skip_whitespace(lexer);
		if (lexer->c == '\0')
			break ;
		if (lexer->c == '>')
			return (out_token(lexer));
		if (lexer->c == '<')
			return (in_token(lexer));
		if (lexer->c == '|')
			return (pipe_token(lexer));
		else
			return (lexer_collect_str(lexer));
	}
	return ((void *)0);
}

t_token	*lexer_collect_str(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (!is_white_space(lexer->c) && !is_special_char(lexer->c))
	{
		if (lexer->c == '\0')
			break ;
		add_up_char(lexer, &value);
		if (lexer->c == '\'' || lexer->c == '"')
			value = lexer_advance_until_closed_quote(lexer, &value);
		else
			lexer_advance(lexer);
	}
	if (!value || value[0] == 0)
	{
		if (value)
			free(value);
		value = 0;
		return ((void *)0);
	}
	return (create_token(TOKEN_STR, &value));
}
