#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "../libft/libft.h"

typedef struct LEXER_STRUCT
{
	char				c;
	unsigned int		i;
	char				*content;
	unsigned int		len;
}	t_lexer;


t_lexer	*init_lexer(char *content);

void	lexer_advance(t_lexer *lexer);

void	lexer_skip_whitespace(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer	*lexer);

t_token	*lexer_collect_q_str(t_lexer *lexer, char quote);

t_token	*lexer_collect_str(t_lexer *lexer);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

char	*lexer_advance_until_closed_quote(t_lexer *lexer, char **value);

char	*lexer_get_current_char_as_string(t_lexer *lexer);

void	add_up_char(t_lexer	*lexer, char **value);

int		is_white_space(char c);

int		is_special_char(char c);

// expanding phase

int		to_be_treated(char *str);

void	ft_substitute(t_lexer *lexer, char **value, t_list **env_list);

void	ft_treat_str(t_token *token, t_list **tokens_list, t_list **env_list);

t_list	*expand_tokens(char	*cmd_line, t_list	**env_list);

void	ft_handle_sq(t_lexer *lexer, char **value);

void	ft_handle_$(t_lexer *lexer, char **value, t_list **env_list);

void	ft_handle_dq(t_lexer *lexer, char **value, t_list **env_list);

void	add_up_str(char **value, char **str_to_add);

void	ft_expand(char **to_expand, t_list **env_list);

// parsing utils

typedef struct s_file
{
	t_token *token;
	int		fd;
}		t_file;

int	is_redir(int type);
int	is_pipe(int type);
int	not_str(int type);

t_list	*create_cmd_list(t_list **tokens_list);

void	check_errors(t_list **tokens_list);		// checks parsing errors

char	**list_to_array(t_list **lst);

#endif
