/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/13 21:35:32 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd);
char	*agglutinate(int fd, char *g_lst_files, char *line);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, unsigned int n);

char	*get_next_line(int fd)
{
	char		*line;
	static char	g_lst_files[(BUFFER_SIZE + 1) * FD_MAX] = "";
	char		*current;
	size_t		linelen;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_MAX <= fd)
		return (NULL);
	current = g_lst_files + (fd * (BUFFER_SIZE + 1));
	if (ft_strchr(current, '\n'))
	{
		linelen = ft_strchr(current, '\n') - current + 2;
		printf("chars are %c, %c, %c\n", *(ft_strchr(current, '\n') - 1), *ft_strchr(current, '\n'), *(ft_strchr(current, '\n') + 1));
		line = ft_strndup(current, linelen);
		if (!line)
			return (NULL);
		ft_strlcpy(current, ft_strchr(current, '\n') + 1,
			BUFFER_SIZE - (int)(ft_strchr(current, '\n') - current) + 1);
		ft_bzero(current + 1 + ft_strlen(current),
			BUFFER_SIZE + 1 - linelen);
		return (line);
	}
	line = ft_strndup(current, ft_strlen(current) + 1);
	if (!line)
		return (NULL);
	ft_bzero(current, BUFFER_SIZE + 1);
	line = agglutinate(fd, current, line);
	return (line);
}

char	*agglutinate(int fd, char *g_lst_files, char *line)
{
	size_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr(line, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, g_lst_files, BUFFER_SIZE);
		if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
			ft_bzero(g_lst_files, BUFFER_SIZE + 1);
		if (bytes_read == 0 && *line)
			return (line);
		else if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin(line, g_lst_files, 1);
		ft_bzero(g_lst_files, BUFFER_SIZE + 1);
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
