/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:50:23 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/20 21:50:26 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_up_str(char **value, char **str_to_add)
{
	size_t	value_size;

	if (*str_to_add)
	{
		value_size = ft_strlen(*value) + ft_strlen(*str_to_add) + 1;
		*value = ft_realloc(*value, value_size * sizeof(char));
		ft_strlcat(*value, *str_to_add, value_size);
		free(*str_to_add);
	}
}

void	add_up_char(t_lexer *lexer, char **value)
{
	char	*s;
	size_t	value_size;

	s = lexer_get_current_char_as_string(lexer);
	value_size = ft_strlen(*value) + ft_strlen(s) + 1;
	*value = ft_realloc(*value, value_size * sizeof(char));
	ft_strlcat(*value, s, value_size);
	if (s)
	{
		free(s);
		s = 0;
	}
}

void	keep_it(char **to_expand)
{
	char	*s;

	s = ft_calloc(2, sizeof(char));
	s[0] = '$';
	s = ft_realloc(s, sizeof(char) * (ft_strlen(*to_expand) + 2));
	ft_strlcat(s, *to_expand, ft_strlen(*to_expand) + 2);
	free(*to_expand);
	*to_expand = s;
}

void	clean_it(char **to_expand, int pretype)
{
	if (is_redir(pretype))
	{
		write(2, "MiniShell: $", 12);
		write(2, *to_expand, ft_strlen(*to_expand));
		write(2, ": ambiguous redirect\n", 21);
		g_estat = -2;
	}
	free(*to_expand);
	*to_expand = 0;
}

void	ft_expand(char **to_expand, t_list **env_list, int pretype)
{
	t_env_content	*content;

	content = get_content(*to_expand, env_list);
	if (!content)
	{
		if (pretype == TOKEN_HRDOC)
			keep_it(to_expand);
		else
			clean_it(to_expand, pretype);
	}
	else
	{
		free(*to_expand);
		*to_expand = ft_strdup(content->value);
	}
}
