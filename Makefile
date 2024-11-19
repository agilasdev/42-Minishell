NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
CFLAGS = $(CC) $(FLAGS)
SRC = lib/create_struct.c lib/expand.c lib/expand1.c lib/expand2.c lib/expand3.c \
	lib/identify_token.c lib/lexer.c lib/lexer1.c lib/lexer2.c lib/parse_errors.c \
	lib/token.c lib/expand_heredoc.c lib/cd_cmd.c lib/clear_list.c lib/echo_cmd.c lib/env_cmd.c lib/env_tools.c \
	lib/errors.c lib/execute_cmd.c lib/exit_cmd.c lib/export_cmd.c lib/heredoc.c \
	lib/minishell.c lib/open_files.c lib/pwd_cmd.c lib/unset_cmd.c lib/utils.c lib/main.c
HEADER = include/minishell.h

all: $(NAME)

$(NAME) : $(HEADER)
	@echo "[Minishell] Compiling files.."
	@$(CFLAGS) lib/*.c -o $(NAME) -g -lreadline -lhistory
	@echo ""

clean :
	@echo "Removing Minishell"
	@rm -f $(NAME)

fclean : clean

re : fclean $(NAME)

.PHONY : all fclean re
