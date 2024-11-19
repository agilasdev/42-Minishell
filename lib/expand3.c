/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:50:32 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 21:50:34 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	not_default_char(t_lexer **alexer, char **value, int *flag, int pretype)
{
	char	next_char;
	t_lexer	*lexer;

	*flag = 0;
	lexer = *alexer;
	next_char = lexer->content[lexer->i + 1];
	if (pretype != TOKEN_HRDOC && next_char != '_' && !ft_isalnum(next_char))
	{
		if (next_char == '?')
		{
			*flag = 1;
			lexer_advance(lexer);
		}
		else if (next_char != '\'' && next_char != '"')
		{
			add_up_char(lexer, value);
			lexer_advance(lexer);
			return (1);
		}
	}
	return (0);
}

void	collect2chars(t_lexer *lexer, char **value)
{
	add_up_char(lexer, value);
	lexer_advance(lexer);
	add_up_char(lexer, value);
	lexer_advance(lexer);
}

void	ft_handle_dollar(t_lexer *lexer, char **value, t_list **env_list,
		int pretype)
{
	int		flag;
	char	*to_expand;

	flag = 0;
	if (not_default_char(&lexer, value, &flag, pretype))
		return ;
	if (ft_isdigit(lexer->content[lexer->i + 1]))
	{
		if (pretype == TOKEN_HRDOC)
			collect2chars(lexer, value);
		else
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
		}
		return ;
	}
	lexer_advance(lexer);
	if (flag)
		to_expand = ft_itoa(g_estat);
	else
		change_varname(&lexer, &to_expand, env_list, pretype);
	add_up_str(value, &to_expand);
}

void	change_varname(t_lexer **alexer, char **to_expand, \
		t_list **env_list, int pretype)
{
	t_lexer	*lexer;

	lexer = *alexer;
	(*to_expand) = ft_calloc(1, sizeof(char));
	while (lexer->c == '_' || ft_isalnum(lexer->c))
	{
		add_up_char(lexer, to_expand);
		lexer_advance(lexer);
	}
	ft_expand(to_expand, env_list, pretype);
}

void	ft_handle_dq(t_lexer *lexer, char **value, t_list **env_list,
		int pretype)
{
	lexer_advance(lexer);
	while (lexer->c != '"')
	{
		if (lexer->c == '$' && lexer->content[lexer->i + 1] != '"')
			ft_handle_dollar(lexer, value, env_list, pretype);
		else
		{
			add_up_char(lexer, value);
			lexer_advance(lexer);
		}
	}
	lexer_advance(lexer);
}
