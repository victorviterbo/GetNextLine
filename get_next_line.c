/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/09 16:49:53 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*agglutinate(int fd, char *g_lst_files, char *line);
char		*ft_strchr(char *str, char c);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*g_lst_files = NULL;

	if (!g_lst_files)
		g_lst_files = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!g_lst_files)
		return (NULL);
	line = ft_strdup(g_lst_files);
	line = agglutinate(fd, g_lst_files, line);
	return (line);
}

static char	*agglutinate(int fd, char *g_lst_files, char *line)
{
	size_t	bytes_read;
	char	*new_block;

	bytes_read = 1;
	new_block = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!new_block || !line)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL && bytes_read)
	{
		bytes_read = read(fd, new_block, BUFFER_SIZE);
		*(new_block + bytes_read) = '\0'; //TODO check +1 ?
		line = ft_strjoin(line, new_block);
		if (!line || !*line)
			return (NULL);
	}
	if (bytes_read)
	{
		ft_strlcpy(g_lst_files, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n')));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
		free(g_lst_files);
	free(new_block);
	return (line);
}

char	*ft_strchr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
