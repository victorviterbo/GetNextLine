/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/11 14:29:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*agglutinate(int fd, char **g_lst_files, char *line);
char		*ft_strchr(const char *s, int c);
static void	free_lst_files(char **g_lst_files);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*g_lst_files = NULL;

	if (!g_lst_files)
		g_lst_files = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!g_lst_files)
		return (NULL);
	line = ft_strdup(g_lst_files);
	if (!line)
		return (NULL);
	line = agglutinate(fd, &g_lst_files, line);
	return (line);
}

static char	*agglutinate(int fd, char **g_lst_files, char *line)
{
	size_t	bytes_read;
	char	*new_block;

	bytes_read = 1;
	if (!line)
		return (NULL);
	new_block = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!new_block)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, new_block, BUFFER_SIZE);
		*(new_block + bytes_read) = '\0';
		line = ft_strjoin(line, new_block, 1);
		if (!line || !*line)
		{
			free(new_block);
			return (NULL);
		}
	}
	if (bytes_read)
	{
		ft_strlcpy(*g_lst_files, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n')));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
		free_lst_files(g_lst_files);
	free(new_block);
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

static void	free_lst_files(char **g_lst_files)
{
	free(*g_lst_files);
	*g_lst_files = NULL;
	return ;
}
