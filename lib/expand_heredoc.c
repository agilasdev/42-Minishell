/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:24:10 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/22 03:28:33 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_heredoc(char **aline, t_list	**env_list)
{
	char	*line;
	char	*newline;
	t_lexer	*lexer;

	line = *aline;
	lexer = init_lexer(line);
	newline = ft_calloc(1, sizeof(char));
	while (lexer->c != '\0')
	{
		if (lexer->c == '$')
			expand_content(lexer, &newline, env_list);
		else
		{
			add_up_char(lexer, &newline);
			lexer_advance(lexer);
		}
	}
	free(*aline);
	*aline = newline;
}

void	expand_content(t_lexer *lexer, char **value, t_list **env_list)
{
	char	nxt_char;
	char	*to_expand;

	nxt_char = lexer->content[lexer->i + 1];
	if (nxt_char == '\'' || nxt_char == '"' || !nxt_char)
	{
		add_up_char(lexer, value);
		lexer_advance(lexer);
	}
	else if (nxt_char != '_' && !ft_isalpha(nxt_char))
	{
		lexer_advance(lexer);
		if (nxt_char == '?')
			ft_sub_estat(&to_expand, &lexer, value);
		if (ft_isdigit(nxt_char))
			lexer_advance(lexer);
	}
	else
	{
		lexer_advance(lexer);
		change_varname(&lexer, &to_expand, env_list, -1);
		add_up_str(value, &to_expand);
	}
}

void	ft_sub_estat(char **to_expand, t_lexer **alexer, char **value)
{
	t_lexer	*lexer;

	lexer = *alexer;
	*to_expand = ft_itoa(g_estat);
	add_up_str(value, to_expand);
	lexer_advance(lexer);
}
