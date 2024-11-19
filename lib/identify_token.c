/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:47:07 by zihihi            #+#    #+#             */
/*   Updated: 2022/09/14 11:47:17 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redir(int type)
{
	if (type == TOKEN_IN || type == TOKEN_OUT
		|| type == TOKEN_HRDOC || type == TOKEN_APP)
		return (1);
	return (0);
}

int	is_pipe(int type)
{
	return (type == TOKEN_PIPE);
}

int	not_str(int type)
{
	return (type != TOKEN_STR);
}
