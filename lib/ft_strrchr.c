/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:47 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/13 15:42:49 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strrchr(const	char *s, int c)
{
	char	*t;

	t = NULL;
	while (*s)
	{
		if (*s == (char) c)
			t = (char *) s;
		s++;
	}
	if (*s == (char) c)
		t = (char *) s;
	return (t);
}
