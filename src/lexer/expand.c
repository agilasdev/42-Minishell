#include "../include/minishell.h"

void	ft_substitute(t_lexer *lexer, char **value, t_list **env_list, int pretype)
{
	if (lexer->c == '\'')
		ft_handle_sq(lexer, value);
	else if (lexer->c == '$')
		ft_handle_$(lexer, value, env_list, pretype);
	else if (lexer->c == '"')
		ft_handle_dq(lexer, value, env_list, pretype);
}

void	ft_sub_lexing(char **value, t_list **tokens_list)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer(*value);
	token = lexer_get_next_token(lexer);
	while (token != 0)
	{
		token->e_type = TOKEN_STR;
		ft_lstadd_back(tokens_list, ft_lstnew(token));
		token = lexer_get_next_token(lexer);
	}
	free(*value);
	*value = 0;
	free(lexer);

}

void	ft_treat_str(t_token *token, t_list **tokens_list, t_list **env_list, int pretype)
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
	free(token->value);
	if (value && value[0] == '\0')
	{
		free(value);
		free(token);
	}
	else
	{
		token->value = value;
		ft_lstadd_back(tokens_list, ft_lstnew(token));
	}
	free(lexer);
	// ft_sub_lexing(&value, tokens_list);
}

t_list	*expand_tokens(char	*cmd_line, t_list	**env_list)
{
	t_lexer	*lexer;
	t_list	*tokens_list = 0;
	t_token	*token = 0;
	int		pretype = -1;

	lexer = init_lexer(cmd_line);
	while ((token = lexer_get_next_token(lexer)) != 0)
	{
		if (g_estat == -1)
		{
			g_estat = 1;
			ft_lstclear(&tokens_list, del_token);
			tokens_list = 0;
			break;
		}
		if (!ft_strcmp(token->value, "\"\"") || !ft_strcmp(token->value, "\'\'"))
		{
			free(token->value);
			token->value = ft_calloc(1, sizeof(char));
			ft_lstadd_back(&tokens_list, ft_lstnew(token));
		}
		else if (token->e_type == TOKEN_STR && to_be_treated(token->value))
				ft_treat_str(token, &tokens_list, env_list, pretype);
		else
			ft_lstadd_back(&tokens_list, ft_lstnew(token));
		pretype = token->e_type;
	}
	free(lexer);

	return (tokens_list);
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

void	add_up_str(char **value, char **str_to_add)
{
	size_t	value_size;

	if (*str_to_add)
	{
		value_size = ft_strlen(*value) + ft_strlen(*str_to_add) + 1;	
		*value = realloc(*value, value_size * sizeof(char));		//implement ft_realloc ('_')
		ft_strlcat(*value, *str_to_add, value_size);
		free(*str_to_add);
	}
}

void	add_up_char(t_lexer	*lexer, char **value)
{
	char	*s;
	size_t	value_size;

	// if (*value == 0)
	// 	*value = ft_calloc(1, sizeof(char));
	s = lexer_get_current_char_as_string(lexer);
	value_size = ft_strlen(*value) + ft_strlen(s) + 1;
	*value = realloc(*value, value_size * sizeof(char));		//implement ft_realloc ('_')
	ft_strlcat(*value, s, value_size);
	if (s)
	{
		free(s);
		s = 0;
	}
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

void	ft_handle_$(t_lexer *lexer, char **value, t_list **env_list, int pretype)
{
	char	next_char;
	int		flag = 0;

	next_char = lexer->content[lexer->i + 1];
	if (pretype != TOKEN_HRDOC && next_char != '_' && !ft_isalnum(next_char))
	{
		// if (next_char == '$')
			// add_up (pid)
		if (next_char == '?')
		{
			flag = 1;
			lexer_advance(lexer);
		}
		else if (next_char != '\'' && next_char != '"')
		{
			add_up_char(lexer, value);
			lexer_advance(lexer);
			return ;
		}
	}
	if (ft_isdigit(lexer->c))
	{
		if (pretype == TOKEN_HRDOC)
		{
			add_up_char(lexer, value);
			add_up_char(lexer, value);
		}
		lexer_advance(lexer);
		return ;
	}
	lexer_advance(lexer);	// skipping $ sign
	char	*to_expand;

	if (flag)
		to_expand = ft_itoa(g_estat);
	else
	{
		to_expand = ft_calloc(1, sizeof(char));
		while (lexer->c == '_' || ft_isalnum(lexer->c))
		{
			add_up_char(lexer, &to_expand);
			lexer_advance(lexer);
		}
		ft_expand(&to_expand, env_list, pretype);
	}
	add_up_str(value, &to_expand);
}

void	ft_handle_dq(t_lexer *lexer, char **value, t_list **env_list, int pretype)
{
	lexer_advance(lexer);
	while (lexer->c != '"')
	{
		if (lexer->c == '$')
			ft_handle_$(lexer, value, env_list, pretype);
		else
		{
			add_up_char(lexer, value);
			lexer_advance(lexer);
		}
	}
	lexer_advance(lexer);
}

void	ft_expand(char **to_expand, t_list **env_list, int pretype)
{
	t_env_content	*content;
	char			*s;

	content = get_content(*to_expand, env_list);
	if (!content)
	{
		if (pretype == TOKEN_HRDOC)
		{
			s = ft_calloc(2, sizeof(char));
			s[0] = '$';
			s = realloc(s, sizeof(char) * (ft_strlen(*to_expand) + 2));
			ft_strlcat(s, *to_expand, ft_strlen(*to_expand) + 2);
			free(*to_expand);
			*to_expand = s;
		}
		else
		{
			if (is_redir(pretype))
			{
				write(2, "MiniShell: $", 12);
				write(2, *to_expand, ft_strlen(*to_expand));
				write(2, ": ambiguous redirect\n", 21);
				g_estat = -1;
			}
			free(*to_expand);
			*to_expand = 0;
		}
	}
	else
	{
		free(*to_expand);
		*to_expand = ft_strdup(content->value);
	}
}
