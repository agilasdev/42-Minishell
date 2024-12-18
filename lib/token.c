/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:55:22 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/21 04:55:25 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_token(int type, char **value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->e_type = type;
	token->value = *value;
	return (token);
}
