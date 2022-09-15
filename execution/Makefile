NAME = exec.a
SRC = *.c
CC = cc
CFLAGS = -Wall -Werror -Wextra
FS = -fsanitize=address
LIB =  /Users/ymourchi/.brew/opt/readline/lib
INCLUDE = /Users/ymourchi/.brew/opt/readline/include
LIBFT = ../libft/libft.a

all: $(NAME)

$(NAME): 
		$(CC) $(CFLAGS) $(FS) $(SRC) gnl/*.c $(LIBFT) utils.c -o $(NAME)

exec: 
	$(CC) $(CFLAGS) -fsanitize=address -lreadline -L $(LIB) -I $(INCLUDE) $(LIBFT) *.c ../lexer/*.c ../parsing/*.c -o minishell

clean:
	rm -f $(NAME)

fclean: clean

re: clean fclean all
