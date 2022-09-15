#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	display_n_free_cmd_list(t_list **cmd);

int main(int argc, char *argv[], char *envp[])
{
	(void) argc; (void) argv; (void) envp;
	t_list *env_list = 0;
	
	fill_env_list(envp, &env_list);
	printf("Enter line: \n");
	char	*line = gnl(0);

	while (line)
	{
		g_estat = 0;
		t_list *tokens_list = expand_tokens(line, &env_list);
		check_errors(&tokens_list);
		t_list *cmd_list = create_cmd_list(&tokens_list);
		display_n_free_cmd_list(&cmd_list);
		free(line);
		// system("leaks test");
		line = gnl(0);
	}
	return (0);
}

const char	*ft_translate_token_type(int type)
{
	switch (type) {
	case 0: return "pipe";
	case 1: return "outfile";
	case 2: return "append_file";
	case 3: return "infile";
	case 4: return "here_doc";
	case 5: return "string";
	default: return ("Unknown type");
	}
}

void	display_list(t_list **flist);
void	display_args(char **args);

void	display_n_free_cmd_list(t_list **cmd)
{
	t_list *tmp = *cmd;
	t_list *inlist;
	t_list *outlist;
	char 	**args;

	while (tmp)
	{
		t_cmd *cmd = tmp->content;

		args = cmd->args;
		outlist = cmd->outlist;
		inlist = cmd->inlist;
		printf("ARGS: \n");
		display_args(args);
		printf("Infiles: \n");
		display_list(&inlist);
		printf("Outfiles: \n");
		display_list(&outlist);
		tmp = tmp->next;
	}
	
}

void	display_list(t_list **flist)
{
	t_list	*tmp = *flist;

	while (!g_estat && tmp)
	{
		t_token *content = tmp->content;
		printf("FILE: `%s`, TYPE: %s\n", content->value, ft_translate_token_type(content->e_type));
		tmp = tmp->next;
	}
}

void	display_args(char **args)
{
	int	i;

	i = 0;
	if (args == 0)
		return ;
	while (!g_estat && args[i])
	{
		printf("[%s] ", args[i]);
		i++;
	}
	printf("\n");
}