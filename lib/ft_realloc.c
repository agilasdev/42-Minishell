/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymourchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:57:49 by ymourchi          #+#    #+#             */
/*   Updated: 2022/09/18 22:57:51 by ymourchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*str;
	int		lent;

	str = 0;
	lent = ft_strlen(ptr);
	str = (char *) malloc(size);
	if (str)
		ft_memmove(str, ptr, lent + 1);
	if (ptr)
		free(ptr);
	return (str);
}
