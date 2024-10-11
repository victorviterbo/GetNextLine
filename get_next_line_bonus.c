/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/11 21:46:31 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*get_next_line(int fd);
static char			*agglutinate(int fd, char *g_lst_files, char *line);
char				*ft_strchr(const char *s, int c);

void				ft_bzero(void *s, unsigned int n);

char	*get_next_line(int fd)
{
	char		*line;
	static char	g_lst_files[(BUFFER_SIZE + 1) * 123] = "";

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(g_lst_files + (fd * (BUFFER_SIZE + 1)));
	if (!line)
		return (NULL);
	line = agglutinate(fd, g_lst_files + (fd * (BUFFER_SIZE + 1)), line);
	return (line);
}

static char	*agglutinate(int fd, char *g_lst_files, char *line)
{
	size_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr(line, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, g_lst_files, BUFFER_SIZE);
		if (bytes_read == 0 && *line)
		{
			ft_bzero(g_lst_files, BUFFER_SIZE);
			return (line);
		}
		if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
		{
			ft_bzero(g_lst_files, BUFFER_SIZE);
			free(line);
			return (NULL);
		}
		line = ft_strjoin(line, g_lst_files, 1);
		ft_bzero(g_lst_files, BUFFER_SIZE);
		if (!line)
			return (NULL);
	}
	ft_strlcpy(g_lst_files, ft_strchr(line, '\n') + 1,
		ft_strlen(ft_strchr(line, '\n')));
	*(ft_strchr(line, '\n') + 1) = '\0';
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (*(s + i))
	{
		if ((unsigned char)*(s + i) == uc)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else
		return (NULL);
}

void	ft_bzero(void *s, unsigned int n)
{
	size_t			i;
	unsigned char	*bs;

	i = 0;
	bs = (unsigned char *)s;
	while (i < n)
	{
		*(bs + i) = 0;
		i++;
	}
	return ;
}
