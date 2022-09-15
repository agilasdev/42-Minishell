#include "../include/minishell.h"

t_lexer	*init_lexer(char *content)
{
 	t_lexer	*lexer;
	
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	lexer->len = ft_strlen(content);
	return lexer;
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < lexer->len)
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);

	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	char *str;

	while (lexer->c != '\0' && lexer->i < lexer->len)
	{
		if (is_white_space(lexer->c))
			lexer_skip_whitespace(lexer);
		if (lexer->c == '\0')
			break ;
		if (lexer->c == '>')
		{
			if (lexer->content[lexer->i + 1] == '>')
			{
				lexer_advance(lexer);
				str = ft_strdup(">>");
				return lexer_advance_with_token(lexer, create_token(TOKEN_APP, &str));
			}
			str = lexer_get_current_char_as_string(lexer);
			return lexer_advance_with_token(lexer, create_token(TOKEN_OUT, &str));
		}
		if (lexer->c == '<')
		{
			if (lexer->content[lexer->i + 1] == '<')
			{
				lexer_advance(lexer);
				str = ft_strdup("<<");
				return lexer_advance_with_token(lexer, create_token(TOKEN_HRDOC, &str));
			}
			str = lexer_get_current_char_as_string(lexer);
			return lexer_advance_with_token(lexer, create_token(TOKEN_IN, &str));
		}
		if (lexer->c == '|')
		{
			str = lexer_get_current_char_as_string(lexer);
			return lexer_advance_with_token(lexer, create_token(TOKEN_PIPE, &str));
		}
		else
			return lexer_collect_str(lexer);
	}
	return (void *)0;
}

t_token	*lexer_collect_str(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	
	while (!is_white_space(lexer->c) && !is_special_char(lexer->c))
	{
		// printf("value: [%s]\n", value);
		if (lexer->c == '\0')
			break ;
		add_up_char(lexer, &value);
		if (lexer->c == '\'' || lexer->c == '"')	//advance until closed single quote
			value = lexer_advance_until_closed_quote(lexer, &value);
		else
			lexer_advance(lexer);
	}
	if (!value || value[0] == 0)
	{
		if (value)
			free(value);
		value = 0;
		return (void *)0;
	}
	// printf("value: [%s], size[%lu]\n", value, sizeof(value));
	return create_token(TOKEN_STR, &value);
}

char	*lexer_advance_until_closed_quote(t_lexer *lexer, char **value)
{
	char	quote;

	quote = lexer->c;
	lexer_advance(lexer);
	while (lexer->c != '\0')
	{
		add_up_char(lexer, value);
		if (lexer->c == quote)
			break;
		lexer_advance(lexer);
	}
	if (lexer->c == quote)
		lexer_advance(lexer);
	else
	{
		ft_putendl_fd("\033[0;31munclosed quote error\033[0m", 2);
		g_estat = 1;
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

	return str;
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
