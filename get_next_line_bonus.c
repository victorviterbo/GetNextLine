/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/14 15:26:45 by vviterbo         ###   ########.fr       */
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

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_MAX <= fd)
		return (NULL);
	current = g_lst_files + (fd * (BUFFER_SIZE + 1));
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strjoin(line, current, 1);
	if (!line)
		return (NULL);
	if (!ft_strchr(line, '\n'))
		line = agglutinate(fd, current, line);
	ft_memmove(current, ft_strchr(current, '\n') + 1,
		ft_strlen(ft_strchr(current, '\n')));
	return (line);
}

char	*agglutinate(int fd, char *current, char *line)
{
	size_t	bytes_read;

	while (ft_strchr(line, '\n') == NULL)
	{
		bytes_read = read(fd, current, BUFFER_SIZE);
		if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
			ft_bzero(current, BUFFER_SIZE + 1);
		if (bytes_read == 0 && *line)
			return (line);
		else if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (NULL);
		}
		*(current + bytes_read) = '\0';
		line = ft_strjoin(line, current, 1);
		if (!line)
			return (NULL);
	}
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
