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
#include "lexer.h"

int	g_estat;

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

// Open files functions
int				open_pipes(t_list *clist);
int				open_infile(t_cmd *cmd);
int				open_outfile(t_cmd *cmd);
int				open_files(t_list **clist, t_list **env_list);
void			write_in_heredoc(char *delim, int *infd, int stat);
void			open_heredoc(t_list *clist);
void			close_pipes(t_list *clist, t_cmd *cmd);

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
#endif
