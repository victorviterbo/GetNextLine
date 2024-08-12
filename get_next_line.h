/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:51:31 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/12 23:13:48 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_open_lines{
	int					fd;
	char				*current_line;
	struct s_open_lines	*next;
}	t_open_lines;


char				*get_next_line(int fd);
static t_open_lines	*new_file(int fd, t_open_lines **g_lst_files);
static char			*ft_strchr(char *str, char c);
static void			free_open_line(t_open_lines *todel,
						t_open_lines **g_lst_files);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(char *str);
char				*ft_strdup(const char *s1);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_calloc(size_t count, size_t size);

#endif