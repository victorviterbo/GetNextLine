/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:51:31 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/16 14:17:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*agglutinate(int fd, char *g_lst_files, char *line);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2, int in_place);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s1, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
