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
