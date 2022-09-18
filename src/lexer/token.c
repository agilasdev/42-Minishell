#include "../include/token.h"
#include <stdlib.h>


#include <stdio.h>

t_token	*create_token(int type, char **value)
{
	t_token	*token;
	
	token = calloc(1, sizeof(t_token));
	token->e_type = type;
	token->value = *value;
	return (token);
}
