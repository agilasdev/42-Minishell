#ifndef TOKEN_H
#define TOKEN_H

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

t_token	*create_token(int type, char **value);

// util for tokenizing phase
const char	*ft_translate_token_type(int type);

#endif
