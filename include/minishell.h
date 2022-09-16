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
# include <sys/uio.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include "token.h"

int	g_estat;

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

// Env list tools
t_env_content	*set_content(char *str);
t_env_content	*get_content(char *var, t_list **elist);
void			fill_env_list(char *envp[], t_list **elist);
char			*concat_envl(char *var, char *value);

// Open files functions
int				open_pipes(t_list *clist);
int				open_infile(t_cmd *cmd);
int				open_outfile(t_cmd *cmd);
int				open_files(t_list **clist, t_list **env_list);
int				write_in_heredoc(char *delim, int *infd, int stat);
int				open_heredoc(t_list *clist);
void			close_pipes(t_list *clist, t_cmd *cmd);
void			wherdoc(char *delim, int *fd, int stat);
int				tkn_herdoc(t_cmd *cmd, t_token *token);

// Built-in functions
int				echo_cmd(char **args, int fd);
int				isflag(char *arg);
int				exit_cmd(char **args, t_list **clist, t_list **elist);
char			*destpath(char **args, t_list **elist);
int				cd_cmd(char **args, t_list **elist);
void			update_pwd(char *curdir, t_list **elist);
void			print_env(t_list **elist, char stat);
int				pwd_cmd(t_list **elist);
int				env_cmd(char **args, t_list **elist);
int				export_cmd(char **args, t_list **elist);
int				is_var_valid(int lc, char *str);
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

void	ft_substitute(t_lexer *lexer, char **value, t_list **env_list, int pretype);

void	ft_treat_str(t_token *token, t_list **tokens_list, t_list **env_list, int pretype);

t_list	*expand_tokens(char	*cmd_line, t_list	**env_list);

void	ft_handle_sq(t_lexer *lexer, char **value);

void	ft_handle_$(t_lexer *lexer, char **value, t_list **env_list, int pretype);

void	ft_handle_dq(t_lexer *lexer, char **value, t_list **env_list, int pretype);

void	add_up_str(char **value, char **str_to_add);

void	ft_expand(char **to_expand, t_list **env_list, int pretype);

// parsing utils


int	is_redir(int type);
int	is_pipe(int type);
int	not_str(int type);

t_list	*create_cmd_list(t_list **tokens_list);

int		ft_error_msg(char *s, int exit_num);
int		check_errors(t_list **tokens_list);		// checks parsing errors
void	errors_cases(int type_curr, int type_next, char *value);

char	**list_to_array(t_list **lst);
void	add_file(t_cmd **acmd, t_list **tmp);
void	add_cmd(t_cmd **acmd, t_list **arglist, t_list **cmd_list);
#endif
