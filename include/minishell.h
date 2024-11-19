/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:37:24 by zihihi            #+#    #+#             */
/*   Updated: 2022/06/30 00:37:38 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>

extern int	g_estat;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct LEXER_STRUCT
{
	char				c;
	unsigned int		i;
	char				*content;
	unsigned int		len;
}	t_lexer;

typedef struct env_node_content
{
	char	*var;
	char	*value;
}	t_env_content;

typedef struct s_cmd
{
	t_list	*inlist;
	t_list	*outlist;
	int		infd;
	int		outfd;
	char	**args;
}	t_cmd;

void			minishell(char *line, t_list **elist);
// Env list tools
t_env_content	*set_content(char *str);
t_env_content	*get_content(char *var, t_list **elist);
void			fill_env_list(char *envp[], t_list **elist);
char			*concat_envl(char *var, char *value);

// Open files functions
int				open_pipes(t_list *clist);
void			close_fds(t_list *clist, t_cmd *cmd);
int				open_infile(t_cmd *cmd);
int				open_outfile(t_cmd *cmd);
int				open_heredoc(t_list *clist, t_list **elist);
int				write_in_heredoc(char *delim, int *infd, int stat, \
				t_list **elist);
void			child_herdoc(char *delim, int *fd, int stat, t_list **elist);

// Built-in functions
int				echo_cmd(char **args, int fd);
int				isflag(char *arg);
int				exit_cmd(char **args, t_list **clist, t_list **elist);
char			*destpath(char **args, t_list **elist);
int				cd_cmd(char **args, t_list **elist);
void			update_pwd(char *curdir, t_list **elist);
void			print_env(t_list **elist, int fd);
void			print_export(t_list **elist, int fd);
int				pwd_cmd(t_list **elist, int fd);
int				env_cmd(char **args, t_list **elist, int fd);
int				export_cmd(char **args, t_list **elist, int fd);
int				is_var_valid(char *str);
void			add_var(int last, char *str, t_list **elist);
int				last_char(char *str, int last);
int				unset_cmd(char **args, t_list **elist);
int				rm_env_elem(void *c, t_list **elist);

//execution functions
char			**create_envp(t_list *elist);
void			execution(t_list **clist, t_list **elist);
void			onecmd(t_list **clist, t_list **elist, char **envp);
void			morecmds(t_list **clist, t_list **elist, char **envp);
void			chcmd(t_list **clist, t_list **elist, t_cmd *cmd, char **envp);
int				isbuiltin(char **args, t_list **elist, int fd);
int				check_path(char **paths, t_cmd *cmd);
void			execute_cmd(t_cmd	*cmd, t_list **elist, char **envp);
void			statexit(int pid, int len);
void			to_lower(char *str);

//clear functions
void			clear_list(char **list);
void			del_cmd(void *content);
void			del_env(void *content);
void			del_token(void	*content);
void			clear_all(t_list **clist, t_list **elist, char **envp);

//error functions
void			print_error(char *cmd, char *err_msg);

//sig functions
void			parent_sig(int sig);
void			child_sig(int sig);
void			heredoc_sig(int sig);

//token struct & func
typedef struct TOKEN_STRUCT
{
	enum
	{
		TOKEN_PIPE,
		TOKEN_OUT,
		TOKEN_APP,
		TOKEN_IN,
		TOKEN_HRDOC,
		TOKEN_STR
	} e_type;
	char	*value;
}	t_token;

t_token			*create_token(int type, char **value);

//lexing functions
t_lexer			*init_lexer(char *content);
t_token			*lexer_get_next_token(t_lexer	*lexer);
t_token			*lexer_collect_str(t_lexer *lexer);
t_token			*lexer_collect_q_str(t_lexer *lexer, char quote);
t_token			*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char			*lexer_advance_until_closed_quote(t_lexer *lexer, char **value);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
char			*lexer_get_current_char_as_string(t_lexer *lexer);
void			add_up_char(t_lexer	*lexer, char **value);
int				is_white_space(char c);
int				is_special_char(char c);

// expanding phase
int				to_be_treated(char *str);
void			ft_substitute(t_lexer *lexer, char **value, \
				t_list **env_list, int pretype);
void			ft_treat_str(t_token *token, t_list **tokens_list, \
				t_list **env_list, int pretype);
t_list			*expand_tokens(char	*cmd_line, t_list	**env_list);
void			ft_handle_sq(t_lexer *lexer, char **value);
void			ft_handle_dollar(t_lexer *lexer, char **value, \
				t_list **env_list, int pretype);
void			ft_handle_dq(t_lexer *lexer, char **value, \
					t_list **env_list, int pretype);
void			add_up_str(char **value, char **str_to_add);
void			ft_expand(char **to_expand, t_list **env_list, int pretype);

// parsing utils
int				is_redir(int type);
int				is_pipe(int type);
int				not_str(int type);

t_list			*create_cmd_list(t_list **tokens_list);
int				ft_error_msg(char *s, int exit_num, int *err_nb);
int				check_errors(t_list **tokens_list);		// checks parsing errors
void			errors_cases(int type_curr, int type_next, \
				char *value, int *err_nb);
char			**list_to_array(t_list **lst);
void			add_file(t_cmd **acmd, t_list **tmp);
void			add_cmd(t_cmd **acmd, t_list **arglist, t_list **cmd_list);
t_token			*out_token(t_lexer *lexer);
t_token			*in_token(t_lexer *lexer);
t_token			*pipe_token(t_lexer *lexer);
void			add_token(t_token **atoken, char **avalue, \
				t_list **tokens_list);
void			keep_it(char **to_expand);
void			clean_it(char **to_expand, int pretype);
void			ft_conditions(t_token *token, t_list **tokens_list, \
				t_list **env_list, int pretype);
void			clear_tknlst(t_token *token, t_list **tokens_list);
void			conditions(t_list **atmp, int *err_nb);
int				not_default_char(t_lexer **alexer, char **value, \
				int *flag, int pretype);
void			change_varname(t_lexer **alexer, char **to_expand, \
				t_list **env_list, int pretype);
void			collect2chars(t_lexer *lexer, char **value);

// here-doc expand
void			expand_heredoc(char **aline, t_list **env_list);
void			expand_content(t_lexer *lexer, char **value, t_list **env_list);
void			ft_sub_estat(char **to_expand, t_lexer **alexer, char **value);
// libft functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_realloc(char *ptr, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c, int *splits);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strcmp(const char *s1, const char *s2);
#endif
