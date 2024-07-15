
SRC  = lexer/main.c lexer/lexer.c lexer/token.c lexer/expand.c parsing/primary_struct.c parsing/parse.c

CC = gcc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
HEADERS = libft/libft.h include/lexer.h include/token.h

all:


$(NAME): $(OBJ) $(LIBFT) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) execution/env_tools.c $(FS) -o $(NAME)
	make clean

$(LIBFT):
	cd libft && make

clean:
	rm -f $(OBJ)
	cd libft && make clean

fclean: clean
	rm -f $(NAME)

re: clean fclean $(NAME)
