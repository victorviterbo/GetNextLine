/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:51:31 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/13 18:22:13 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

#include <libc.h>



# ifndef FD_MAX
#  define FD_MAX 13
# endif

char	*get_next_line(int fd);
char	*agglutinate(int fd, char *g_lst_files, char *line);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2, int free_s1);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s1, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t count, size_t size);

#endif