/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihihi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:03:51 by zihihi            #+#    #+#             */
/*   Updated: 2022/01/05 10:33:14 by zihihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "libft.h"
# define BUFFER_SIZE 42

// unsigned int	ft_strlen(char *str);
int				nl_in(char **str);
char			*gnl(int fd);
// char			*ft_strdup(char *s1);
char			*strjoin(char **addr_s1, char **addr_s2);
char			*ft_strjoin(char *s1, char *s2);
char			*deal_with_nl(char **str, int i, char **to_free);
char			*treat(char **astock, int rd, char **to_free);


int	here_doc(char *delim, char flag); /// for here_doc test
#endif
