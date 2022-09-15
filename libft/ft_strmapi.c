/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 04:08:26 by zihihi            #+#    #+#             */
/*   Updated: 2021/11/27 17:53:47 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*str;
	unsigned int	l;
	unsigned int	i;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < l)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
/*#include <stdio.h>
char	func(unsigned int i, char c)
{
	if (c == 'l')
		return ('s');
	return (c);
}
int main(void)
{
	char *s = ft_strdup("hello world!");
	char *new_s = ft_strmapi(s, func);
	printf("%s\n", new_s);
	return (0);
}*/
