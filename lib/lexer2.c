/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:03:10 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 15:03:12 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_advance_until_closed_quote(t_lexer *lexer, char **value)
{
	char	quote;

	quote = lexer->c;
	lexer_advance(lexer);
	while (lexer->c != '\0')
	{
		add_up_char(lexer, value);
		if (lexer->c == quote)
			break ;
		lexer_advance(lexer);
	}
	if (lexer->c == quote)
		lexer_advance(lexer);
	else
	{
		ft_putendl_fd("MiniShell: unclosed quote error", 2);
		g_estat = -1;
		if (*value)
		{
			free(*value);
			*value = 0;
		}
	}
	return (*value);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
